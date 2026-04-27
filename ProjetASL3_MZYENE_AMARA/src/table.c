#define _GNU_SOURCE
#include "table.h"

SymbolTable *globalTable = NULL;

/* ===================== UTILS ===================== */

static SymbolTable *new_entry(symbol_kind k, const char *id)
{
    SymbolTable *e = calloc(1, sizeof *e);
    e->kind = k;
    e->id = strdup(id);
    e->next = globalTable;
    globalTable = e;
    return e;
}

SymbolTable *find_symbol(SymbolTable *t, const char *id)
{
    for (; t; t = t->next)
        if (!strcmp(t->id, id))
            return t;
    return NULL;
}

/* ===================== SIZE ===================== */

static int sizeof_tpc(const char *t)
{
    if (!t) return 4;

    if (!strcmp(t, "int")) return 4;
    if (!strcmp(t, "char")) return 1;
    if (!strcmp(t, "double")) return 8;

    /* struct */
    SymbolTable *s = find_symbol(globalTable, t);
    if (s && s->kind == STRUCT_TYPE)
        return s->data.structure.size;

    return 4;
}

/* ===================== VARIABLES ===================== */

void add_global(const char *name, const char *type)
{
    if (find_symbol(globalTable, name)) {
        fprintf(stderr, "Erreur: redéfinition de %s\n", name);
        exit(2);
    }

    SymbolTable *e = new_entry(VARIABLE, name);
    e->data.variable.type = strdup(type);
    e->size = sizeof_tpc(type);
}

/* ===================== STRUCT ===================== */

static void add_struct(Node *n)
{
    Node *nameNode = n->firstChild;
    Node *fieldsNode = nameNode->nextSibling;

    const char *name = nameNode->value;

    if (find_symbol(globalTable, name)) {
        fprintf(stderr, "Struct %s déjà définie\n", name);
        exit(2);
    }

    SymbolTable *e = new_entry(STRUCT_TYPE, name);

    int offset = 0;
    int count = 0;
    struct_field *fields = NULL;

    for (Node *f = fieldsNode->firstChild; f; f = f->nextSibling) {

        Node *typeNode = f->firstChild;
        Node *decls = typeNode->nextSibling;

        const char *type = typeNode->value;

        /* cas struct */
        if (!strcmp(type, "struct"))
            type = typeNode->firstChild->value;

        for (Node *idN = decls->firstChild; idN; idN = idN->nextSibling) {

            fields = realloc(fields, sizeof(struct_field)*(count+1));

            fields[count].field_name = strdup(idN->value);
            fields[count].field_type = strdup(type);
            fields[count].offset = offset;

            offset += sizeof_tpc(type);
            count++;
        }
    }

    e->data.structure.fields = fields;
    e->data.structure.field_count = count;
    e->data.structure.size = offset;
}

/* ===================== FONCTIONS ===================== */

static void add_function(Node *n)
{
    Node *header = n->firstChild;

    Node *retNode = header->firstChild;
    Node *nameNode = retNode->nextSibling;

    const char *fname = nameNode->value;
    const char *rtype = retNode->value;

    if (find_symbol(globalTable, fname)) {
        fprintf(stderr, "Fonction %s déjà définie\n", fname);
        exit(2);
    }

    SymbolTable *e = new_entry(FUNCTION, fname);
    e->data.function.return_type = strdup(rtype);

    /* paramètres */
    var *params = NULL;
    int count = 0;

    Node *paramNode = nameNode->nextSibling;

    if (paramNode && paramNode->label == Parametres) {

        Node *list = paramNode->firstChild;

        if (list && list->label == ListTypVar) {

            for (Node *p = list->firstChild; p; p = p->nextSibling) {

                Node *typeNode = p->firstChild;
                Node *idNode = typeNode->nextSibling;

const char *param_id = idNode->value;

            for (int j = 0; j < count; j++) {
                if (!strcmp(params[j].id, param_id)) {
                    fprintf(stderr, "Erreur: paramètre '%s' dupliqué dans la fonction %s\n", param_id, fname);
                    exit(2);
                }
            }

            params = realloc(params, sizeof(var)*(count+1));
            params[count].type = strdup(typeNode->value);
            params[count].id = strdup(param_id);

                count++;
            }
        }
    }

    e->data.function.params = params;
    e->data.function.param_count = count;
}

/* ===================== TRAVERSAL ===================== */

void traverse_ast_and_create_table(Node *n)
{
    if (!n) return;

    /* ===================== STRUCT ===================== */
    if (n->label == StructDecl) {
        add_struct(n);
    }

    /* ===================== VARIABLES ===================== */
    if (n->label == DeclVars) {

        for (Node *decl = n->firstChild; decl; decl = decl->nextSibling) {

            if (!decl || !decl->firstChild) continue;

            Node *typeNode = decl->firstChild;
            Node *decls = typeNode->nextSibling;

            if (!typeNode || !decls) continue;

            const char *type = typeNode->value;

            /* struct type */
            if (type && !strcmp(type, "struct") && typeNode->firstChild)
                type = typeNode->firstChild->value;

            if (!decls->firstChild) continue;

            for (Node *idN = decls->firstChild; idN; idN = idN->nextSibling) {

                if (!idN || !idN->value) continue;

                add_global(idN->value, type);
            }
        }
    }

    /* ===================== FONCTIONS ===================== */
    if (n->label == DeclFonct) {
        add_function(n);
    }

    /* ===================== RECURSION SAFE ===================== */

    if (n->firstChild)
        traverse_ast_and_create_table(n->firstChild);

    if (n->nextSibling)
        traverse_ast_and_create_table(n->nextSibling);
}

/* ===================== PRINT ===================== */

void print_symbols_table(SymbolTable *s)
{
    printf("\n=== TABLE DES SYMBOLES ===\n");

    while (s) {
        if (s->kind == VARIABLE) {
            printf("VAR   %-10s | type=%s | size=%d\n",
                   s->id,
                   s->data.variable.type,
                   s->size);
        }
        else if (s->kind == FUNCTION) {
            printf("FUNC  %-10s | return=%s\n",
                   s->id,
                   s->data.function.return_type);

            for (int i = 0; i < s->data.function.param_count; i++) {
                printf("  PARAM %-10s | type=%s\n",
                       s->data.function.params[i].id,
                       s->data.function.params[i].type);
            }
        }
        else if (s->kind == STRUCT_TYPE) {
            printf("STRUCT %-10s | size=%d\n",
                   s->id,
                   s->data.structure.size);

            for (int i = 0; i < s->data.structure.field_count; i++) {
                printf("  FIELD %-10s | type=%s | offset=%d\n",
                       s->data.structure.fields[i].field_name,
                       s->data.structure.fields[i].field_type,
                       s->data.structure.fields[i].offset);
            }
        }

        s = s->next;
    }
}

/* ===================== FREE ===================== */

void free_SymbolTable(SymbolTable *s)
{
    while (s) {
        SymbolTable *n = s->next;

        free(s->id);

        if (s->kind == VARIABLE) {
            free(s->data.variable.type);
        }
        else if (s->kind == FUNCTION) {
            free(s->data.function.return_type);
            for (int i = 0; i < s->data.function.param_count; i++) {
                free(s->data.function.params[i].type);
                free(s->data.function.params[i].id);
            }
            free(s->data.function.params);
        }
        else if (s->kind == STRUCT_TYPE) {
            for (int i = 0; i < s->data.structure.field_count; i++) {
                free(s->data.structure.fields[i].field_name);
                free(s->data.structure.fields[i].field_type);
            }
            free(s->data.structure.fields);
        }

        free(s);
        s = n;
    }
}