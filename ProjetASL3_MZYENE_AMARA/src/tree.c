/* tree.c */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
extern int lineno;       /* from lexer */
Node *ast_root = NULL;

static const char *StringFromLabel[] = {
  "Programme",                  // Programme
  "DeclVars",                   // DeclVars
  "Declarateurs",               // Declarateurs
  "StructDecls",                // StructDecls
  "StructDecl",                 // StructDecl
  "StructFields",               // StructFields
  "StructField",                // StructField
  "DeclFoncts",                 // DeclFoncts
  "DeclFonct",                  // DeclFonct
  "EnTeteFonct",                // EnTeteFonct
  "Parametres",                 // Parametres
  "ListTypVar",                 // ListTypVar
  "Corps",                      // Corps
  "SuiteInstr",                 // SuiteInstr
  "Instr",                      // Instr
  "Exp",                        // Exp
  "TB",                         // TB
  "FB",                         // FB
  "M",                          // M
  "E",                          // E
  "T",                          // T
  "F",                          // F
  "Arguments",                  // Arguments
  "ListExp",                    // ListExp
  "DIVSTAR",                    // divstar
  "id",                         // id
  "num"                         // num
};

Node *makeNode(label_t label, char* value) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    fprintf(stderr, "Run out of memory\n"); 
    exit(1);
  }

  node->label = label;
  node->firstChild = node->nextSibling = NULL;
  node->lineno = lineno;

  if (value != NULL) {
    size_t len = strlen(value);
    node->value = malloc(len + 1);
    if (!node->value) {
      fprintf(stderr, "Run out of memory\n"); 
      free(node);
      exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++) {
      node->value[i] = value[i];
    }
    node->value[len] = '\0';
  } else node->value = NULL;

  return node;
}

void addSibling(Node *node, Node *sibling) {
  if (!node || !sibling) return;
  Node *curr = node;
  while (curr->nextSibling != NULL) {
    curr = curr->nextSibling;
  }
  curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
  if (!parent || !child) return;
  if (parent->firstChild == NULL) {
    parent->firstChild = child;
  }
  else {
    addSibling(parent->firstChild, child);
  }
}

void deleteTree(Node *node) {
  if (!node) return;
  if (node->firstChild) {
    deleteTree(node->firstChild);
  }
  if (node->nextSibling) {
    deleteTree(node->nextSibling);
  }
  if (node->value) {
    free(node->value);
  }
  free(node);
}

void printTree(Node *node) {
  static bool rightmost[128]; // tells if node is rightmost sibling
  static int depth = 0;       // depth of current node
  if (!node) return;
  for (int i = 1; i < depth; i++) { // 2502 = vertical line
    printf(rightmost[i] ? "    " : "\u2502   ");
  }
  if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical line and right horiz 
    printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
  }
  if (!node->value){
  	printf("%s", StringFromLabel[node->label]);
  } else {
  	printf("%s", node->value);
  }
  printf("\n");
  depth++;
  for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
    rightmost[depth] = (child->nextSibling) ? false : true;
    printTree(child);
  }
  depth--;
}
