#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "table.h"
#include "tree.h"

static void check_node(Node *n);

#define SEM_ERR(fmt, ...) \
  do { fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__); error_count++; } while(0)

#define SEM_WAR(fmt, ...) \
  do { fprintf(stderr, "[WARN] " fmt "\n", ##__VA_ARGS__); warning_count++; } while(0)

/* ================= GLOBAL STATE ================= */

static int error_count = 0;
static int warning_count = 0;

static SymbolTable *current_fn = NULL;
static SymbolTable *current_locals = NULL;
static int has_return = 0;

/* ================= UTIL ================= */

static int is_same(const char *a, const char *b) {
    return a && b && strcmp(a, b) == 0;
}

/* ================= LOOKUP ================= */

/*
 * Cherche un symbole : d'abord dans les paramètres de la fonction courante,
 * puis dans la portée locale, puis dans la table globale.
 * Retourne NULL si non trouvé.
 */
/*
 * Retourne le type d'un identifiant (variable, paramètre, ou type de retour
 * d'une fonction). Retourne NULL si non trouvé.
 */
static const char *lookup_type(const char *name) {
    if (!name) return NULL;

    /* paramètres */
    if (current_fn) {
        for (int i = 0; i < current_fn->data.function.param_count; i++) {
            var p = current_fn->data.function.params[i];
            if (!strcmp(p.id, name))
                return p.type;
        }
    }

    /* portée locale */
    for (SymbolTable *s = current_locals; s; s = s->next) {
        if (s->kind == VARIABLE && !strcmp(s->id, name))
            return s->data.variable.type;
    }

    SymbolTable *s = find_symbol(globalTable, name);
    if (!s) return NULL;

    if (s->kind == VARIABLE)
        return s->data.variable.type;

    if (s->kind == FUNCTION)
        return s->data.function.return_type;

    return NULL;
}

static void free_local_variables(void) {
    while (current_locals) {
        SymbolTable *next = current_locals->next;
        free(current_locals->id);
        free(current_locals->data.variable.type);
        free(current_locals);
        current_locals = next;
    }
}

static int add_local_variable(const char *name, const char *type) {
    if (!name || !type) return 0;

    for (SymbolTable *s = current_locals; s; s = s->next) {
        if (s->kind == VARIABLE && !strcmp(s->id, name)) {
            SEM_ERR("redéfinition de %s", name);
            return 0;
        }
    }

    if (current_fn) {
        for (int i = 0; i < current_fn->data.function.param_count; i++) {
            var p = current_fn->data.function.params[i];
            if (!strcmp(p.id, name)) {
                SEM_ERR("redéfinition de %s", name);
                return 0;
            }
        }
    }

    SymbolTable *entry = calloc(1, sizeof *entry);
    entry->kind = VARIABLE;
    entry->id = strdup(name);
    entry->data.variable.type = strdup(type);
    entry->next = current_locals;
    current_locals = entry;
    return 1;
}

static void collect_local_variables(Node *n) {
    if (!n) return;

    if (n->label == DeclVars) {
        for (Node *decl = n->firstChild; decl; decl = decl->nextSibling) {
            if (!decl || !decl->firstChild) continue;

            Node *typeNode = decl->firstChild;
            Node *decls = typeNode->nextSibling;
            if (!typeNode || !decls) continue;

            const char *type = typeNode->value;
            if (type && !strcmp(type, "struct") && typeNode->firstChild)
                type = typeNode->firstChild->value;

            for (Node *idN = decls->firstChild; idN; idN = idN->nextSibling) {
                if (!idN || !idN->value) continue;
                add_local_variable(idN->value, type);
            }
        }
        return;
    }

    for (Node *child = n->firstChild; child; child = child->nextSibling)
        collect_local_variables(child);
}

/* ================= TYPE INFERENCE ================= */

/*
 * Infer the type of an expression node.
 *
 * AST shapes produced by the grammar:
 *
 *   Literal integer  : num node, value = "42"
 *   Variable         : id node, value = "x", no children
 *   Unary op         : id node, value = "-" or "!", one child
 *   Binary op        : id node, value = "+"/"-"/…, two children
 *   Function call    : id node, value = "call",
 *                        firstChild      = id(fname)
 *                        firstChild->next = Arguments node
 *                                             -> ListExp -> Exp*
 *
 * The grammar wraps all of the above inside intermediate nodes
 * (Exp, TB, FB, M, E, T, F).  We unwrap by recursing into single-
 * child intermediate nodes transparently.
 */
static const char *infer_expr_type(Node *n) {
    if (!n) return "int";

    /* ── Transparent wrapper (Exp/TB/FB/M/E/T/F with one child) ── */
    if (n->label != id && n->label != num) {
        if (n->firstChild && !n->firstChild->nextSibling)
            return infer_expr_type(n->firstChild);
        /* multi-child intermediate: recurse on first child
           (binary ops are stored directly as id nodes already) */
        if (n->firstChild)
            return infer_expr_type(n->firstChild);
        return "int";
    }

    /* ── Integer literal ── */
    if (n->label == num)
        return "int";

    /* n->label == id from here on */

    /* ── Function call:  id("call") → id(fname) [→ Arguments] ── */
    if (n->value && strcmp(n->value, "call") == 0) {
        Node *fnNode = n->firstChild;
        if (!fnNode || !fnNode->value) return "int";

        const char *fname = fnNode->value;
        SymbolTable *s = find_symbol(globalTable, fname);

        if (!s || s->kind != FUNCTION) {
            SEM_ERR("fonction inconnue '%s'", fname);
            return "int";
        }

        if (is_same(s->data.function.return_type, "void"))
            SEM_ERR("utilisation d'une fonction void dans une expression ('%s')", fname);

        /* arguments: Arguments → ListExp → Exp* */
        Node *argsNode = fnNode->nextSibling;          /* Arguments or ListExp or NULL */
        Node *listExp  = argsNode;
        if (listExp && listExp->label == Arguments)
            listExp = listExp->firstChild;
        Node *a = NULL;
        if (listExp) {
            if (listExp->label == ListExp)
                a = listExp->firstChild;
            else
                a = listExp;
        }

        int expected = s->data.function.param_count;
        int actual   = 0;
        for (Node *tmp = a; tmp; tmp = tmp->nextSibling) actual++;

        if (actual != expected) {
            SEM_ERR("nb args incorrect pour '%s' (%d attendu, %d trouvé)",
                    fname, expected, actual);
            return s->data.function.return_type;
        }

        for (int i = 0; i < expected; i++) {
            const char *expected_t = s->data.function.params[i].type;
            const char *actual_t   = infer_expr_type(a);

            if (!is_same(expected_t, actual_t))
                SEM_ERR("type argument %d incorrect pour '%s' (%s attendu, %s trouvé)",
                        i + 1, fname, expected_t, actual_t);

            a = a->nextSibling;
        }

        return s->data.function.return_type;
    }

    /* ── Unary operator:  id("-" or "!") with exactly one child ── */
    if (n->value && n->firstChild && !n->firstChild->nextSibling) {
        if (strcmp(n->value, "!") == 0)  return "int";
        if (strcmp(n->value, "-") == 0)  return infer_expr_type(n->firstChild);
        if (strcmp(n->value, "+") == 0)  return infer_expr_type(n->firstChild);
    }

    /* ── Binary operator:  id(op) with two children ── */
    if (n->value && n->firstChild && n->firstChild->nextSibling) {
        const char *t1 = infer_expr_type(n->firstChild);
        const char *t2 = infer_expr_type(n->firstChild->nextSibling);

        if (!t1 || !t2) return "int";

        /* relational / equality operators → int (boolean) */
        if (strcmp(n->value, "==") == 0 || strcmp(n->value, "!=") == 0 ||
            strcmp(n->value, "<")  == 0 || strcmp(n->value, ">")  == 0 ||
            strcmp(n->value, "<=") == 0 || strcmp(n->value, ">=") == 0 ||
            strcmp(n->value, "&&") == 0 || strcmp(n->value, "||") == 0)
            return "int";

        /* arithmetic: promote to double if either operand is double */
        if (is_same(t1, "double") || is_same(t2, "double"))
            return "double";

        return "int";
    }

    /* ── Plain identifier (variable or parameter) ── */
    if (n->value) {
        const char *t = lookup_type(n->value);
        if (!t) {
            SEM_ERR("variable non déclarée '%s'", n->value);
            return "int";
        }
        return t;
    }

    return "int";
}

/* ================= FUNCTION BODY ================= */

static void handle_function(Node *n) {
    if (!n || !n->firstChild) return;

    Node *hdr   = n->firstChild;          /* EnTeteFonct */
    Node *retN  = hdr->firstChild;        /* type node   */
    Node *nameN = retN ? retN->nextSibling : NULL;

    if (!nameN || !nameN->value) return;

    const char *fname = nameN->value;

    current_fn = find_symbol(globalTable, fname);
    has_return  = 0;

    if (!current_fn) {
        SEM_ERR("fonction inconnue '%s'", fname);
        return;
    }

    /* collecter les variables locales de la fonction */
    current_locals = NULL;
    collect_local_variables(n);

    /* parcourir le corps */
    for (Node *c = n->firstChild; c; c = c->nextSibling)
        check_node(c);

    free_local_variables();
    current_locals = NULL;

    /* avertissement si une fonction non-void ne contient aucun return */
    if (!is_same(current_fn->data.function.return_type, "void") && !has_return)
        SEM_WAR("fonction '%s' sans instruction return", fname);

    current_fn = NULL;
}

/* ================= NODE CHECKER ================= */

static void check_node(Node *n) {
    if (!n) return;

    /* ── Déclaration de fonction : déléguer ── */
    if (n->label == DeclFonct) {
        handle_function(n);
        return;
    }

    /* ── Déclarations de variables : pas de vérification ici ── */
    if (n->label == DeclVars) {
        return;
    }

    /* ── Nœuds non-instruction : descendre ── */
    if (n->label != Instr) {
        for (Node *c = n->firstChild; c; c = c->nextSibling)
            check_node(c);
        return;
    }

    /* ── Instruction ── */
    Node *c = n->firstChild;
    if (!c || !c->value) {
        /* instruction vide ou bloc vide */
        for (Node *child = n->firstChild; child; child = child->nextSibling)
            check_node(child);
        return;
    }

    /* ─── return ─── */
    if (strcmp(c->value, "return") == 0) {
        has_return = 1;

        if (!current_fn) {
            SEM_ERR("return hors d'une fonction");
            return;
        }

        Node *expr  = c->firstChild;
        const char *retT = current_fn->data.function.return_type;

        if (!expr) {
            /* return; */
            if (!is_same(retT, "void"))
                SEM_ERR("return sans valeur dans une fonction de type '%s'", retT);
        } else {
            /* return <expr>; */
            if (is_same(retT, "void")) {
                SEM_ERR("return avec valeur dans une fonction void");
            } else {
                const char *exprT = infer_expr_type(expr);
                if (!is_same(retT, exprT))
                    SEM_ERR("type de retour incorrect ('%s' attendu, '%s' trouvé)",
                            retT, exprT);
            }
        }
    }

    /* ─── affectation ─── */
    else if (strcmp(c->value, "=") == 0) {
        Node *lhs = c->firstChild;
        Node *rhs = lhs ? lhs->nextSibling : NULL;

        if (!lhs || !rhs) return;

        if (!lhs->value) {
            SEM_ERR("membre gauche d'affectation invalide");
            return;
        }

        const char *lt = lookup_type(lhs->value);
        if (!lt) {
            SEM_ERR("variable non déclarée '%s'", lhs->value);
            return;
        }

        const char *rt = infer_expr_type(rhs);

        if (is_same(rt, "void"))
            SEM_ERR("affectation d'une expression de type void");
        else if (!is_same(lt, rt))
            SEM_ERR("types incompatibles dans l'affectation ('%s' = '%s')", lt, rt);
    }

    /* ─── if ─── */
    else if (strcmp(c->value, "if") == 0) {
        Node *cond  = c->firstChild;
        Node *then  = cond ? cond->nextSibling : NULL;

        if (cond) {
            if (is_same(infer_expr_type(cond), "void"))
                SEM_ERR("condition de type void dans 'if'");
            if (cond->label == num)
                SEM_WAR("condition constante dans 'if' (%s)", cond->value);
        }

        /* vérifier le corps then */
        if (then) check_node(then);
    }

    /* ─── if…else ─── */
    else if (strcmp(c->value, "ifelse") == 0) {
        Node *cond  = c->firstChild;
        Node *then  = cond ? cond->nextSibling : NULL;
        Node *els   = then ? then->nextSibling : NULL;

        if (cond) {
            if (is_same(infer_expr_type(cond), "void"))
                SEM_ERR("condition de type void dans 'if…else'");
            if (cond->label == num)
                SEM_WAR("condition constante dans 'if…else' (%s)", cond->value);
        }

        if (then) check_node(then);
        if (els)  check_node(els);
    }

    /* ─── while ─── */
    else if (strcmp(c->value, "while") == 0) {
        Node *cond = c->firstChild;
        Node *body = cond ? cond->nextSibling : NULL;

        if (cond) {
            if (is_same(infer_expr_type(cond), "void"))
                SEM_ERR("condition de type void dans 'while'");
            if (cond->label == num)
                SEM_WAR("condition constante dans 'while' (%s)", cond->value);
        }

        if (body) check_node(body);
    }

    /* ─── appel de fonction (instruction) ─── */
    else if (strcmp(c->value, "call") == 0) {
        Node *fnNode  = c->firstChild;
        if (!fnNode || !fnNode->value) return;

        const char *fname = fnNode->value;
        SymbolTable *s    = find_symbol(globalTable, fname);

        if (!s || s->kind != FUNCTION) {
            SEM_ERR("fonction inconnue '%s'", fname);
            return;
        }

        /* arguments : Arguments → ListExp → Exp* */
        Node *argsNode = fnNode->nextSibling;
        Node *listExp  = argsNode;
        if (listExp && listExp->label == Arguments)
            listExp = listExp->firstChild;
        Node *a = NULL;
        if (listExp) {
            if (listExp->label == ListExp)
                a = listExp->firstChild;
            else
                a = listExp;
        }

        int expected = s->data.function.param_count;
        int actual   = 0;
        for (Node *tmp = a; tmp; tmp = tmp->nextSibling) actual++;

        if (actual != expected) {
            SEM_ERR("nb args incorrect pour '%s' (%d attendu, %d trouvé)",
                    fname, expected, actual);
            return;
        }

        for (int i = 0; i < expected; i++) {
            const char *expected_t = s->data.function.params[i].type;
            const char *actual_t   = infer_expr_type(a);

            if (!is_same(expected_t, actual_t))
                SEM_ERR("type argument %d incorrect pour '%s' (%s attendu, %s trouvé)",
                        i + 1, fname, expected_t, actual_t);

            a = a->nextSibling;
        }
    }

    /* ─── bloc { } ─── */
    else if (strcmp(c->value, "block") == 0) {
        for (Node *child = c->firstChild; child; child = child->nextSibling)
            check_node(child);
        return; /* ne pas repasser sur c via la boucle finale */
    }

    /* ─── descente générale ─── */
    for (Node *child = n->firstChild; child; child = child->nextSibling)
        check_node(child);
}

/* ================= ENTRY POINT ================= */

int check_semantics(Node *root) {
    error_count   = 0;
    warning_count = 0;

    if (!root) return 2;

    check_node(root);

    /* Vérification de la fonction main */
    SymbolTable *main_sym = find_symbol(globalTable, "main");

    if (!main_sym || main_sym->kind != FUNCTION)
        SEM_ERR("fonction 'main' manquante");
    else if (!is_same(main_sym->data.function.return_type, "int"))
        SEM_ERR("'main' doit retourner 'int'");

    return (error_count > 0) ? 2 : 0;
}