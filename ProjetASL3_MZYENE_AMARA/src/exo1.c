#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"



FILE *out;
extern int lineno;  


void parcourir_ast(Node *node);


void traiter_fonction(Node *node) {
    if (node == NULL) return;

  
    Node *entete = FIRSTCHILD(node);

    if (entete && entete->label == EnTeteFonct && entete->value != NULL) {
        if (strcmp(entete->value, "main") == 0) {
         
            fprintf(out, "global _start\n");
            fprintf(out, "section .text\n");
            fprintf(out, "_start:\n");

        
            Node *corps = SECONDCHILD(node); 
            parcourir_ast(corps);

            fprintf(out, "mov rax, 60\n"); 
            fprintf(out, "mov rdi, 0\n");   
            fprintf(out, "syscall\n");
        }
    }
}


void parcourir_ast(Node *node) {
    if (node == NULL) return;

    switch(node->label) {
        case DeclFonct:
            traiter_fonction(node);
            break;

        case SuiteInstr:
        case Instr:
            fprintf(out, "; instruction ligne %d\n", node->lineno);
            break;

        default:
            break;
    }

    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
        parcourir_ast(child);
    }
}


int main(int argc, char **argv) {

    out = fopen("_anonymous.asm", "w");
    if (!out) {
        perror("Erreur ouverture fichier _anonymous.asm");
        exit(1);
    }

  
    extern Node* root;
    
    if (root != NULL) {
        parcourir_ast(root);
    }

    fclose(out);

    return 0;
}