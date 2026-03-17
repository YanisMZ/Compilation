#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/* ============================= */
/* Structure de la table symbole */
/* ============================= */

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

/* ============================= */
/* Création table                */
/* ============================= */

SymbolTable* createTable() {
    SymbolTable *table = malloc(sizeof(SymbolTable));
    table->head = NULL;
    return table;
}

/* ============================= */
/* Recherche identificateur      */
/* ============================= */

Symbol* lookup(SymbolTable *table, const char *name) {

    Symbol *curr = table->head;

    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;

        curr = curr->next;
    }

    return NULL;
}

/* ============================= */
/* Insertion avec vérification   */
/* ============================= */

Symbol* insert(SymbolTable *table, const char *name, const char *type, SymKind kind) {

    Symbol *found = lookup(table, name);

    if (found)
        return found;

    Symbol *sym = malloc(sizeof(Symbol));

    strcpy(sym->name, name);
    strcpy(sym->type, type);
    sym->kind = kind;

    sym->next = table->head;
    table->head = sym;

    return sym;
}

/* ============================= */
/* Affichage table               */
/* ============================= */

void printTable(SymbolTable *table) {

    printf("\n===== TABLE DES SYMBOLES =====\n");

    Symbol *curr = table->head;

    while (curr) {

        printf("Nom: %s | Type: %s | Kind: %d\n",
               curr->name,
               curr->type,
               curr->kind);

        curr = curr->next;
    }
}

/* ================================= */
/* Remplir table des variables globales */
/* ================================= */

void fillGlobalVars(SymbolTable *table, Node *declvars) {

    if (!declvars) return;

    for (Node *decl = declvars->firstChild; decl; decl = decl->nextSibling) {

        Node *typeNode = FIRSTCHILD(decl);
        Node *ids = SECONDCHILD(decl);

        if (!typeNode || !ids) continue;

        char *type = typeNode->value;

        for (Node *idNode = ids->firstChild; idNode; idNode = idNode->nextSibling) {

            insert(table, idNode->value, type, SYM_VAR_GLOBAL);
        }
    }
}

/* ============================= */
/* Remplir paramètres fonction   */
/* ============================= */

void fillParams(SymbolTable *table, Node *params) {

    if (!params) return;

    Node *list = FIRSTCHILD(params);

    if (!list) return;

    for (Node *p = list->firstChild; p; p = p->nextSibling) {

        Node *typeNode = FIRSTCHILD(p);
        Node *idNode = SECONDCHILD(p);

        if (!typeNode || !idNode) continue;

        insert(table, idNode->value, typeNode->value, SYM_PARAM);
    }
}

/* ============================= */
/* Variables locales             */
/* ============================= */

void fillLocalVars(SymbolTable *table, Node *declvars) {

    if (!declvars) return;

    for (Node *decl = declvars->firstChild; decl; decl = decl->nextSibling) {

        Node *typeNode = FIRSTCHILD(decl);
        Node *ids = SECONDCHILD(decl);

        if (!typeNode || !ids) continue;

        char *type = typeNode->value;

        for (Node *idNode = ids->firstChild; idNode; idNode = idNode->nextSibling) {

            insert(table, idNode->value, type, SYM_VAR_LOCAL);
        }
    }
}

/* ============================= */
/* Parcours AST pour fonctions   */
/* ============================= */

void buildFunctionTables(Node *node) {

    if (!node) return;

    if (node->label == DeclFonct) {

        printf("\n--- Fonction trouvée ---\n");

        SymbolTable *table = createTable();

        Node *header = FIRSTCHILD(node);
        Node *body = SECONDCHILD(node);

        Node *params = THIRDCHILD(header);

        fillParams(table, params);

        Node *declvars = FIRSTCHILD(body);

        fillLocalVars(table, declvars);

        printTable(table);
    }

    buildFunctionTables(node->firstChild);
    buildFunctionTables(node->nextSibling);
}

/* ============================= */
/* Construction complète tables  */
/* ============================= */

void buildSymbolTables(Node *root) {

    if (!root) return;

    SymbolTable *globalTable = createTable();

    Node *declVars = SECONDCHILD(root);

    fillGlobalVars(globalTable, declVars);

    printf("\nTABLE DES VARIABLES GLOBALES\n");

    printTable(globalTable);

    Node *functions = THIRDCHILD(root);

    buildFunctionTables(functions);
}