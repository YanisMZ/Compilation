/* symtable.h */

#ifndef SYMTABLE_H
#define SYMTABLE_H

typedef enum {
    SYM_VAR_GLOBAL,
    SYM_VAR_LOCAL,
    SYM_PARAM,
    SYM_FUNCTION
} SymKind;

typedef struct Symbol {
    char name[64];
    char type[64];
    SymKind kind;
    struct Symbol *next;
} Symbol;

typedef struct {
    Symbol *head;
} SymbolTable;

SymbolTable* createTable();
Symbol* lookup(SymbolTable *table, const char *name);
Symbol* insert(SymbolTable *table, const char *name, const char *type, SymKind kind);
void printTable(SymbolTable *table);

#endif