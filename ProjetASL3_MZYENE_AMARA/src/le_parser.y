%{
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <getopt.h> 

extern int yylineno;
extern char* yytext;
int yylex();

int lineno = 1; // défini pour tree.c
Node *root = NULL; // racine de l'arbre

void yyerror(const char *s) {
    fprintf(stderr, "Erreur de syntaxe à la ligne %d: %s", yylineno, s);
    if (yytext) fprintf(stderr, " --> : '%s'", yytext);
    printf("\n");
}

void print_help() {
    printf("Usage: tpcas [OPTIONS]\n");
    printf("Options:\n");
    printf("  -t, --tree       Affiche l'arbre abstrait sur la sortie standard\n");
    printf("  -h, --help       Affiche cette aide et termine l'exécution\n");
}
%}

%union {
    int num;
    char character;
    char id[64];
    Node *node;
}

%token <character> CHARACTER
%token <num> NUM
%token <id> IDENT
%token <id> TYPE
%token <id> STRUCT
%token <id> VOID
%token IF ELSE RETURN WHILE
%token <id> ADDSUB DIVSTAR AND OR EQ ORDER

%type <node> Prog DeclVars Declarateurs StructDecls StructDecl StructFields StructField DeclFoncts DeclFonct 
              EnTeteFonct Parametres ListTypVar Corps SuiteInstr Instr Exp TB FB M E T F 
              Arguments ListExp 

%start Prog
%expect 4
%%

Prog:
    StructDecls DeclVars DeclFoncts {
        Node *tmp = makeNode(Programme, NULL);
        if ($1) addChild(tmp, $1);
        if ($2) addChild(tmp, $2);
        if ($3) addChild(tmp, $3);
        $$ = tmp;
        root = tmp;
    }
;




StructDecls:
      StructDecls StructDecl {
          Node *tmp = $1 ? $1 : makeNode(StructDecls, NULL);
          addChild(tmp, $2);
          $$ = tmp;
      }
    | StructDecl {
          Node *tmp = makeNode(StructDecls, NULL);
          addChild(tmp, $1);
          $$ = tmp;
      }
    | { $$ = NULL; }
;

StructDecl:
    STRUCT IDENT '{' StructFields '}' ';' {
        Node *tmp = makeNode(StructDecl, NULL);
        addChild(tmp, makeNode(id, $2));  // nom de la structure
        addChild(tmp, $4);                // champs de la structure
        $$ = tmp;
    }
;

StructFields:
      StructFields StructField {
          Node *tmp = $1 ? $1 : makeNode(StructFields, NULL);
          addChild(tmp, $2);
          $$ = tmp;
      }
    | StructField {
          Node *tmp = makeNode(StructFields, NULL);
          addChild(tmp, $1);
          $$ = tmp;
      }
;

StructField:
      TYPE Declarateurs ';' {
          Node *tmp = makeNode(StructField, NULL);
          addChild(tmp, makeNode(id, $1));
          addChild(tmp, $2);
          $$ = tmp;
      }
    | STRUCT IDENT Declarateurs ';' {
          Node *tmp = makeNode(StructField, NULL);
          addChild(tmp, makeNode(id, $2)); // type struct déjà déclaré
          addChild(tmp, $3);               // noms des champs
          $$ = tmp;
      }
;




DeclVars:
    DeclVars TYPE Declarateurs ';' {
        Node *tmp = $1 ? $1 : makeNode(DeclVars, NULL);
        Node *decl = makeNode(DeclVars, NULL);
        addChild(decl, makeNode(id, $2));
        addChild(decl, $3);
        addChild(tmp, decl);
        $$ = tmp;
    }
  | DeclVars STRUCT IDENT Declarateurs ';' {
        Node *tmp = $1 ? $1 : makeNode(DeclVars, NULL);
        Node *decl = makeNode(DeclVars, NULL);
        Node *structType = makeNode(id, "struct");
        addChild(structType, makeNode(id, $3)); // struct aircraft
        addChild(decl, structType);
        addChild(decl, $4); // a1, a2, etc.
        addChild(tmp, decl);
        $$ = tmp;
    }
  | STRUCT IDENT Declarateurs ';' {  // <── ajout clé !
        Node *tmp = makeNode(DeclVars, NULL);
        Node *decl = makeNode(DeclVars, NULL);
        Node *structType = makeNode(id, "struct");
        addChild(structType, makeNode(id, $2));
        addChild(decl, structType);
        addChild(decl, $3);
        addChild(tmp, decl);
        $$ = tmp;
    }
  | { $$ = NULL; }
;



Declarateurs:
    Declarateurs ',' IDENT {
        Node *tmp = $1 ? $1 : makeNode(Declarateurs, NULL);
        addChild(tmp, makeNode(id, $3));
        $$ = tmp;
    }
  | IDENT {
        Node *tmp = makeNode(Declarateurs, NULL);
        addChild(tmp, makeNode(id, $1));
        $$ = tmp;
    }
;



DeclFoncts:
    DeclFoncts DeclFonct {
        Node *tmp = $1 ? $1 : makeNode(DeclFoncts, NULL);
        addChild(tmp, $2);
        $$ = tmp;
    }
  | DeclFonct {
        Node *tmp = makeNode(DeclFoncts, NULL);
        addChild(tmp, $1);
        $$ = tmp;
    }
;

DeclFonct:
    EnTeteFonct Corps {
        Node *tmp = makeNode(DeclFonct, NULL);
        addChild(tmp, $1);
        addChild(tmp, $2);
        $$ = tmp;
    }
;

EnTeteFonct:
    TYPE IDENT '(' Parametres ')' {
        Node *tmp = makeNode(EnTeteFonct, NULL);
        addChild(tmp, makeNode(id, $1));
        addChild(tmp, makeNode(id, $2));
        if ($4) addChild(tmp, $4);
        $$ = tmp;
    }
  | VOID IDENT '(' Parametres ')' {
        Node *tmp = makeNode(EnTeteFonct, NULL);
        addChild(tmp, makeNode(id, $1));
        addChild(tmp, makeNode(id, $2));
        if ($4) addChild(tmp, $4);
        $$ = tmp;
    }
;

Parametres:
    VOID {
        Node *tmp = makeNode(Parametres, NULL);
        addChild(tmp, makeNode(id, $1));
        $$ = tmp;
    }
  | ListTypVar {
        Node *tmp = makeNode(Parametres, NULL);
        addChild(tmp, $1);
        $$ = tmp;
    }
;

ListTypVar:
    ListTypVar ',' TYPE IDENT {
        Node *tmp = $1 ? $1 : makeNode(ListTypVar, NULL);
        Node *param = makeNode(Parametres, NULL);
        addChild(param, makeNode(id, $3));
        addChild(param, makeNode(id, $4));
        addChild(tmp, param);
        $$ = tmp;
    }
  | TYPE IDENT {
        Node *tmp = makeNode(ListTypVar, NULL);
        Node *param = makeNode(Parametres, NULL);
        addChild(param, makeNode(id, $1));
        addChild(param, makeNode(id, $2));
        addChild(tmp, param);
        $$ = tmp;
    }
;



Corps:
    '{' DeclVars SuiteInstr '}' {
        Node *tmp = makeNode(Corps, NULL);
        if ($2) addChild(tmp, $2);   
        if ($3) addChild(tmp, $3);   
        $$ = tmp;
    }
;




SuiteInstr:
    SuiteInstr Instr {
        Node *tmp = $1 ? $1 : makeNode(SuiteInstr, NULL);
        addChild(tmp, $2);
        $$ = tmp;
    }
  | { $$ = NULL; }
;

Instr:
    IDENT '=' Exp ';'
    {
      Node *tmp = makeNode(Instr, NULL);
      Node *opNode = makeNode(id, "=");
      addChild(opNode, makeNode(id, $1));
      addChild(opNode, $3);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | IF '(' Exp ')' Instr
    {
      Node *tmp = makeNode(Instr, NULL);
      Node *ifNode = makeNode(id, "if");
      addChild(ifNode, $3);
      addChild(ifNode, $5);
      addChild(tmp, ifNode);
      $$ = tmp;
    }
  | IF '(' Exp ')' Instr ELSE Instr
    {
      Node *tmp = makeNode(Instr, NULL);
      Node *ifNode = makeNode(id, "ifelse");
      addChild(ifNode, $3);
      addChild(ifNode, $5);
      addChild(ifNode, $7);
      addChild(tmp, ifNode);
      $$ = tmp;
    }
  | WHILE '(' Exp ')' Instr
    {
      Node *tmp = makeNode(Instr, NULL);
      Node *whileNode = makeNode(id, "while");
      addChild(whileNode, $3);
      addChild(whileNode, $5);
      addChild(tmp, whileNode);
      $$ = tmp;
    }
  | IDENT '(' Arguments ')' ';'
    {
      Node *tmp = makeNode(Instr, NULL);
      Node *callNode = makeNode(id, "call");
      addChild(callNode, makeNode(id, $1));
      if ($3) addChild(callNode, $3);
      addChild(tmp, callNode);
      $$ = tmp;
    }
  | RETURN Exp ';'
    {
      Node *tmp = makeNode(Instr, NULL);
      Node *retNode = makeNode(id, "return");
      addChild(retNode, $2);
      addChild(tmp, retNode);
      $$ = tmp;
    }
  | RETURN ';'
    {
      Node *tmp = makeNode(Instr, NULL);
      Node *retNode = makeNode(id, "return");
      addChild(tmp, retNode);
      $$ = tmp;
    }
  | '{' SuiteInstr '}'
    {
      if ($2) {
        Node *tmp = makeNode(Instr, NULL);
        Node *blockNode = makeNode(id, "block");
        addChild(blockNode, $2);
        addChild(tmp, blockNode);
        $$ = tmp;
      } else {
        $$ = makeNode(Instr, "empty_block");
      }
    }
  | ';'
    {
      $$ = makeNode(Instr, "empty_instr");
    }
;

Exp:
    Exp OR TB
    {
      Node *tmp = makeNode(Exp, NULL);
      Node *opNode = makeNode(id, "||");
      addChild(opNode, $1);
      addChild(opNode, $3);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | TB
    { $$ = $1; }
;

TB:
    TB AND FB
    {
      Node *tmp = makeNode(TB, NULL);
      Node *opNode = makeNode(id, "&&");
      addChild(opNode, $1);
      addChild(opNode, $3);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | FB
    { $$ = $1; }
;

FB:
    FB EQ M
    {
      Node *tmp = makeNode(FB, NULL);
      Node *opNode = makeNode(id, $2);
      addChild(opNode, $1);
      addChild(opNode, $3);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | M
    { $$ = $1; }
;

M:
    M ORDER E
    {
      Node *tmp = makeNode(M, NULL);
      Node *opNode = makeNode(id, $2);
      addChild(opNode, $1);
      addChild(opNode, $3);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | E
    { $$ = $1; }
;

E:
    E ADDSUB T
    {
      Node *tmp = makeNode(E, NULL);
      Node *opNode = makeNode(id, $2);
      addChild(opNode, $1);
      addChild(opNode, $3);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | T
    { $$ = $1; }
;

T:
    T DIVSTAR F
    {
      Node *tmp = makeNode(T, NULL);
      Node *opNode = makeNode(id, $2);
      addChild(opNode, $1);
      addChild(opNode, $3);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | F
    { $$ = $1; }
;

F:
    ADDSUB F
    {
      Node *tmp = makeNode(F, NULL);
      Node *opNode = makeNode(id, $1);
      addChild(opNode, $2);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | '!' F
    {
      Node *tmp = makeNode(F, NULL);
      Node *opNode = makeNode(id, "!");
      addChild(opNode, $2);
      addChild(tmp, opNode);
      $$ = tmp;
    }
  | '(' Exp ')'
    {
      $$ = $2;
    }
  | NUM
    {
      char buf[32];
      snprintf(buf, sizeof(buf), "%d", $1);
      $$ = makeNode(num, buf);
    }
  | CHARACTER
    {
      char buf[2];
      buf[0] = $1;
      buf[1] = '\0';
      $$ = makeNode(id, buf);
    }
  | IDENT
    {
      $$ = makeNode(id, $1);
    }
  | IDENT '(' Arguments ')'
    {
      Node *tmp = makeNode(F, NULL);
      Node *callNode = makeNode(id, "call");
      addChild(callNode, makeNode(id, $1));
      if ($3) addChild(callNode, $3);
      addChild(tmp, callNode);
      $$ = tmp;
    }
;

Arguments:
    ListExp
    { $$ = $1; }
  | 
    { $$ = NULL; }
;

ListExp:
    ListExp ',' Exp
    {
      Node *tmp = $1 ? $1 : makeNode(ListExp, NULL);
      addChild(tmp, $3);
      $$ = tmp;
    }
  | Exp
    {
      Node *tmp = makeNode(ListExp, NULL);
      addChild(tmp, $1);
      $$ = tmp;
    }
;


%%

int yyparse();

int main(int argc, char *argv[]) {
    int opt, show_tree = 0;

    struct option long_options[] = {
        {"tree", no_argument, NULL, 't'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "th", long_options, NULL)) != -1) {
        switch (opt) {
            case 't': show_tree = 1; break;
            case 'h': print_help(); return 0;
            default:
                fprintf(stderr, "Option invalide : -%c\n", opt);
                print_help(); return 2;
        }
    }

    printf("Début de l'analyse syntaxique...\n");
    if (yyparse() == 0) {
        printf("Analyse syntaxique réussie.\n");
        if (show_tree && root) printTree(root);
        return 0;
    } else {
        printf("Erreur d'analyse syntaxique.\n");
        return 1;
    }
}
