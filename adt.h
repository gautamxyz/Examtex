#ifndef __BUILD_AST
#define __BUILD_AST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int NUMQ;
int NUMF;
float DQ,DF;
typedef struct TreeNode Node;
typedef Node *PtrToNode;

struct TreeNode
{
    char Array[100];
    PtrToNode NextSibling;
    PtrToNode FirstChild;
};


void Parseqp(FILE* q);


#endif
