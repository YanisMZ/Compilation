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

    /* params */
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

    if (n->label == num)
        return "int";

    /* 🔥 FIX IMPORTANT : check identifiants */
    if (n->label == id && n->value) {
        const char *t = lookup_type(n->value);

        if (!t) {
            SEM_ERR("variable non déclarée %s", n->value);
            return "int";
        }

        return t;
    }

    /* unary */
    if (n->firstChild && !n->firstChild->nextSibling && n->value) {
        if (!strcmp(n->value, "!")) return "int";
        if (!strcmp(n->value, "-")) return infer_expr_type(n->firstChild);
    }

    /* binary */
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

/* ================= DECL ================= */

static void check_decl_vars(Node *n) {
    (void)n;
    /* table déjà gérée ailleurs */
}

/* ================= FUNCTION ================= */

static void handle_function(Node *n) {
    if (!n || !n->firstChild) return;

    Node *hdr = n->firstChild;
    Node *retN = hdr->firstChild;
    Node *nameN = retN ? retN->nextSibling : NULL;

    if (!nameN) return;

    const char *fname = nameN->value;

    current_fn = find_symbol(globalTable, fname);
    has_return = 0;

    if (!current_fn) {
        SEM_ERR("fonction inconnue %s", fname);
        return;
    }

    for (Node *c = n->firstChild; c; c = c->nextSibling)
        check_node(c);

    if (!is_same(current_fn->data.function.return_type, "void") && !has_return)
        SEM_WAR("fonction '%s' sans return", fname);

    current_fn = NULL;
}

/* ================= CORE ================= */

static void check_node(Node *n) {
    if (!n) return;

    if (n->label == DeclFonct) {
        handle_function(n);
        return;
    }

    if (n->label == DeclVars) {
        check_decl_vars(n);
        return;
    }

    if (n->label != Instr) {
        for (Node *c = n->firstChild; c; c = c->nextSibling)
            check_node(c);
        return;
    }

    Node *c = n->firstChild;
    if (!c) return;

    /* ================= RETURN ================= */
    if (!strcmp(c->value, "return")) {
        has_return = 1;

        if (!current_fn) {
            SEM_ERR("return hors fonction");
            return;
        }

        Node *expr = c->firstChild;
        const char *retT = current_fn->data.function.return_type;

        if (!expr && !is_same(retT, "void"))
            SEM_ERR("return vide non void");

        if (expr && !is_same(retT, infer_expr_type(expr)))
            SEM_ERR("type return incorrect");
    }

    /* ================= ASSIGN ================= */
    else if (!strcmp(c->value, "=")) {

        Node *lhs = c->firstChild;
        Node *rhs = lhs ? lhs->nextSibling : NULL;

        if (!lhs || !rhs) return;

        const char *lt = lookup_type(lhs->value);

        /* 🔥 IMPORTANT FIX */
        if (!lt) {
            SEM_ERR("variable non déclarée %s", lhs->value);
            return;
        }

        const char *rt = infer_expr_type(rhs);

        if (is_same(rt, "void"))
            SEM_ERR("assignation void");
    }

    /* ================= IF / WHILE ================= */
    else if (!strcmp(c->value, "if") || !strcmp(c->value, "while")) {
        Node *cond = c->firstChild;
        if (cond && cond->label == num)
            SEM_WAR("condition constante %s", cond->value);
    }

    /* ================= CALL ================= */
    else if (!strcmp(c->value, "call")) {

        Node *fn = c->firstChild;
        if (!fn) return;

        SymbolTable *s = find_symbol(globalTable, fn->value);

        if (!s || s->kind != FUNCTION) {
            SEM_ERR("fonction inconnue %s", fn->value);
            return;
        }

        int expected = s->data.function.param_count;
        int actual = 0;

        Node *args = fn->nextSibling;
        for (Node *a = args ? args->firstChild : NULL; a; a = a->nextSibling)
            actual++;

        if (actual != expected)
            SEM_ERR("nb args incorrect %s", fn->value);
    }
}

/* ================= ENTRY ================= */

int check_semantics(Node *root) {
    error_count = 0;
    warning_count = 0;

    if (!root) return 2;

    check_node(root);

    SymbolTable *main = find_symbol(globalTable, "main");

    if (!main || main->kind != FUNCTION)
        SEM_ERR("fonction main manquante");
    else if (!is_same(main->data.function.return_type, "int"))
        SEM_ERR("main doit retourner int");

    return (error_count > 0) ? 2 : 0;
}