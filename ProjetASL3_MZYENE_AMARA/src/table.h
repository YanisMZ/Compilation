#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* ───────── catégories ───────── */
typedef enum { VARIABLE, FUNCTION, STRUCT_TYPE } symbol_kind;

/* ---------- structures ---------- */

typedef struct {
    char *type;
    char *id;
} var;

/* ----- fonction ----- */
typedef struct {
    char  *return_type;
    var   *params;
    int    param_count;
} func;

/* ----- struct ----- */
typedef struct {
    char *field_name;
    char *field_type;
    int offset;
} struct_field;

typedef struct {
    struct_field *fields;
    int field_count;
    int size;
} struct_def;

/* ----- symbole ----- */
typedef struct SymbolTable {
    symbol_kind  kind;
    char        *id;

    union {
        var variable;
        func function;
        struct_def structure;
    } data;

    int   size;
    char *address;
    char *extra;

    struct SymbolTable *next;
} SymbolTable;

/* table globale */
extern SymbolTable *globalTable;

/* API */
SymbolTable *find_symbol(SymbolTable *, const char *);
SymbolTable *find_symbol_kind(SymbolTable *, const char *, symbol_kind);
void traverse_ast_and_create_table(Node *);
void print_symbols_table(SymbolTable *);
void free_symbols_table(SymbolTable *);
void add_global(const char *name, const char *type);

#endif