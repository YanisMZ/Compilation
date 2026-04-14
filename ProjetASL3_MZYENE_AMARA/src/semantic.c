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
static int has_return = 0;

/* ================= UTIL ================= */

static int is_same(const char *a, const char *b) {
    return a && b && strcmp(a, b) == 0;
}

/* ================= LOOKUP ================= */

static const char *lookup_type(const char *name) {
    if (!name) return NULL;

    if (current_fn) {
        for (int i = 0; i < current_fn->data.function.param_count; i++) {
            var p = current_fn->data.function.params[i];
            if (!strcmp(p.id, name))
                return p.type;
        }
    }

    SymbolTable *s = find_symbol(globalTable, name);
    if (!s) return NULL;

    if (s->kind == VARIABLE)
        return s->data.variable.type;

    if (s->kind == FUNCTION)
        return s->data.function.return_type;

    return NULL;
}

/* ================= TYPE INFERENCE ================= */

static const char *infer_expr_type(Node *n) {
    if (!n) return "int";

    if (n->label == num) return "int";

    if (n->label == id && n->value) {
        const char *t = lookup_type(n->value);
        return t ? t : "int";
    }

    if (n->label == Instr && n->value && !strcmp(n->value, "call")) {
        Node *fn = n->firstChild;
        if (!fn) return "int";

        SymbolTable *s = find_symbol(globalTable, fn->value);
        if (!s || s->kind != FUNCTION) return "int";

        return s->data.function.return_type;
    }

    if (n->firstChild && !n->firstChild->nextSibling && n->value) {
        if (!strcmp(n->value, "!")) return "int";
        if (!strcmp(n->value, "-")) return infer_expr_type(n->firstChild);
    }

    if (n->firstChild && n->firstChild->nextSibling && n->value) {
        const char *t1 = infer_expr_type(n->firstChild);
        const char *t2 = infer_expr_type(n->firstChild->nextSibling);

        if (strstr(n->value, "==") || strstr(n->value, "<") ||
            strstr(n->value, ">") || strstr(n->value, "!"))
            return "int";

        if (!strcmp(t1, "double") || !strcmp(t2, "double"))
            return "double";

        return "int";
    }

    return "int";
}

/* ================= DECL CHECK ================= */

static void check_decl_vars(Node *n) {
    for (Node *d = n->firstChild; d; d = d->nextSibling) {
        if (!d || !d->firstChild) continue;

        Node *typeN = d->firstChild;
        Node *ids = typeN->nextSibling;
        const char *type = typeN->value;

        if (!type || !ids) continue;

        if (!strcmp(type, "struct") && typeN->firstChild)
            type = typeN->firstChild->value;

        for (Node *idN = ids->firstChild; idN; idN = idN->nextSibling) {
            if (!idN || !idN->value) continue;

            if (find_symbol(globalTable, idN->value))
                SEM_ERR("variable déjà déclarée %s", idN->value);
            else
                add_global(idN->value, type);
        }
    }
}

/* ================= FUNCTION ================= */

static void handle_function(Node *n) {
    if (!n || !n->firstChild) return;

    Node *hdr = n->firstChild;
    Node *retN = hdr->firstChild;
    Node *nameN = retN ? retN->nextSibling : NULL;

    if (!nameN) return;

    const char *fname = nameN->value;

    has_return = 0;
    current_fn = find_symbol(globalTable, fname);

    if (!current_fn) {
        SEM_ERR("fonction inconnue %s", fname);
        return;
    }

    /* double function check */
    for (SymbolTable *s = globalTable; s; s = s->next) {
        if (s->kind == FUNCTION && s != current_fn &&
            !strcmp(s->id, fname))
            SEM_ERR("fonction déjà déclarée %s", fname);
    }

    /* param duplicates */
    for (int i = 0; i < current_fn->data.function.param_count; i++) {
        for (int j = i + 1; j < current_fn->data.function.param_count; j++) {
            if (!strcmp(current_fn->data.function.params[i].id,
                        current_fn->data.function.params[j].id))
                SEM_ERR("paramètre dupliqué %s",
                        current_fn->data.function.params[i].id);
        }
    }

    for (Node *c = n->firstChild; c; c = c->nextSibling)
        check_node(c);

    if (!is_same(current_fn->data.function.return_type, "void") && !has_return)
        SEM_WAR("fonction '%s' sans return", fname);

    current_fn = NULL;
}


/* ================= CORE CHECK ================= */

static void check_node(Node *n) {
    if (!n) return;

    /* function */
    if (n->label == DeclFonct) {
        handle_function(n);
        return;
    }

    /* variables */
    if (n->label == DeclVars) {
        check_decl_vars(n);
    }

    /* if / while */
    if (n->label == Instr && n->value &&
        (!strcmp(n->value, "if") || !strcmp(n->value, "while"))) {

        Node *cond = n->firstChild;
        if (cond && cond->label == num) {
            SEM_WAR("condition constante %s", cond->value);
        }
    }

    /* return */
    if (n->label == Instr && n->value && !strcmp(n->value, "return")) {
        has_return = 1;

        if (!current_fn) {
            SEM_ERR("return hors fonction");
        } else {
            Node *expr = n->firstChild;
            const char *retT = current_fn->data.function.return_type;

            if (!expr && !is_same(retT, "void"))
                SEM_ERR("return vide non void");

            if (expr && is_same(retT, "void"))
                SEM_ERR("return avec valeur dans void");

            if (expr && !is_same(retT, infer_expr_type(expr)))
                SEM_ERR("type return incorrect");
        }
    }

    /* assignment */
    if (n->label == Instr && n->value && !strcmp(n->value, "=")) {
        Node *lhs = n->firstChild;
        Node *rhs = lhs ? lhs->nextSibling : NULL;

        if (!lhs || !rhs) return;

        const char *lt = lookup_type(lhs->value);
        const char *rt = infer_expr_type(rhs);

        if (!lt)
            SEM_ERR("variable non déclarée %s", lhs->value);

        if (is_same(rt, "void"))
            SEM_ERR("assignation void");
    }

    /* function call */
    if (n->label == Instr && n->value && !strcmp(n->value, "call")) {

        Node *fn = n->firstChild;
        if (!fn) return;

        SymbolTable *s = find_symbol(globalTable, fn->value);

        if (!s || s->kind != FUNCTION) {
            SEM_ERR("fonction inconnue %s", fn->value);
        } else {
            int expected = s->data.function.param_count;
            int actual = 0;

            Node *args = fn->nextSibling;
            for (Node *a = args ? args->firstChild : NULL; a; a = a->nextSibling)
                actual++;

            if (actual != expected)
                SEM_ERR("nb args incorrect %s", fn->value);

            if (is_same(s->data.function.return_type, "void"))
                SEM_WAR("appel de fonction void %s", fn->value);
        }
    }

    for (Node *c = n->firstChild; c; c = c->nextSibling)
        check_node(c);
}

/* ================= ENTRY ================= */

int check_semantics(Node *root) {
    error_count = 0;
    warning_count = 0;

    check_node(root);

    /* main check */
    SymbolTable *main = find_symbol(globalTable, "main");

    if (!main || main->kind != FUNCTION)
        SEM_ERR("fonction main manquante");
    else if (!is_same(main->data.function.return_type, "int"))
        SEM_ERR("main doit retourner int");

    if (warning_count)
        fprintf(stderr, "%d warnings\n", warning_count);

    return error_count ? 2 : 0;
}