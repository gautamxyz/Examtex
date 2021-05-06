#ifndef __BUILD_AST
#define __BUILD_AST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float DQ[2], DF[2];
int NUMQ;
int NUMF;


int  NUMMCQ ;
int  NUMFILL ;

typedef struct TreeNode Node;
typedef Node *PtrToNode;

struct TreeNode
{
    char Array[300];
    PtrToNode NextSibling;
    PtrToNode FirstChild;
};

void Parseqp(FILE *q);
PtrToNode MakeNode();
PtrToNode InitTree();
void MakePtrsToQues(int n, PtrToNode MCQArray[], int m, PtrToNode FILLArray[]);
PtrToNode ParseBank(FILE *fp);
void MakeQuesPaperFile(PtrToNode Root);
int getkey(int , int);

#endif