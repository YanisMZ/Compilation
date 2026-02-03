/* tree.h */
#ifndef TREE_H
#define TREE_H

typedef enum {
  Programme,
  DeclVars,
  StructDecls,
  StructDecl,
  StructFields,
  StructField,
  Declarateurs,
  DeclFoncts,
  DeclFonct,
  EnTeteFonct,
  Parametres,
  ListTypVar,
  Corps,
  SuiteInstr,
  Instr,
  Exp,
  TB,
  FB,
  M,
  E,
  T,
  F,
  Arguments,
  ListExp,
  divstar,
  id,
  num
} label_t;

typedef struct Node {
  label_t label;
  struct Node *firstChild, *nextSibling;
  int lineno;
  char* value;
} Node;

Node *makeNode(label_t label, char *value);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling

#endif /* tree.h */
