#include "ast.h"

int main(void)
{

  //  FILE *Nfp = fopen("questionpaper.txt", "w"); //appends i.e,creates questionbank.txt filegcc 
    FILE *fp = fopen("questionbank.txt", "r");
    FILE *q=fopen("qp.txt","r");

    Parseqp(q);

    PtrToNode Root = ParseBank(fp); // Parses the data into an abstarct syntax tre

    MakeQuesPaperFile(Root);

    return 0;
}