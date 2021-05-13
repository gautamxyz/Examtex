#ifndef __BUILD_AST
#define __BUILD_AST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float DQ[2], DF[2];
int NUMQ; // number of mcqs user wants in each question paper
int NUMF; // number of fill in the blanks user wants in each question paper


int  NUMMCQ ; // total number of mcqs in question bank
int  NUMFILL ; // total number of fill in the blanks in question bank

typedef struct TreeNode Node;
typedef Node *PtrToNode;

struct TreeNode
{
    char Array[500];
    PtrToNode NextSibling;
    PtrToNode FirstChild;
};

void Parseqp(FILE *q); // parses qp.txt
PtrToNode MakeNode(); // Creates and initialises a node
PtrToNode InitTree(); // Initialises tree (ast)
void MakePtrsToQues(int n, PtrToNode MCQArray[], int m, PtrToNode FILLArray[]); // makes pointers to questions
PtrToNode ParseBank(FILE *fp); // parses question bank into ast
void MakeQuesPaperFile(PtrToNode Root); // outputs 3 question papers in .md format
int getkey(int , int); // gets key

#endif
