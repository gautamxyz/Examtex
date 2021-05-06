#include "ast.h"
#include <time.h>
PtrToNode MCQQuestionsAddress[100], FILLQuestionsAddress[100];

void Parseqp(FILE *q)
{
    char string[10];
    char type;
    char num[5];
    while (!feof(q))
    {
        fgets(string, 10, q);
        // printf("Done\n");

        if (string[0] == 'T')
        {
            //printf("done\n");
            type = string[4];
        }
        else if (string[0] == 'N' && type == 'm')
        {
            strcpy(num, &string[4]);
            int x = atoi(num);
            NUMQ = x;
        }
        else if (string[0] == 'N' && type == 'f')
        {
            strcpy(num, &string[4]);
            int x = atoi(num);
            NUMF = x;
        }
        else if (string[0] == 'D' && type == 'm')
        {
            strcpy(num, &string[5]);
            float x = atof(num);
            if (string[2] == '<')
                DQ[1] = x;
            else if (string[2] == '>')
                DQ[0] = x;
        }
        else if (string[0] == 'D' && type == 'f')
        {
            strcpy(num, &string[5]);
            float x = atof(num);
            if (string[2] == '<')
                DF[1] = x;
            else if (string[2] == '>')
                DF[0] = x;
        }
    }
    // printf("done1\n");
    //printf("%d %d\n", NUMQ, NUMF);)
    //printf("%f %f\n", DQ, DF);)
}

PtrToNode MakeNode()
{
    PtrToNode P = (PtrToNode)malloc(sizeof(Node));

    P->FirstChild = NULL;
    P->NextSibling = NULL;

    return P;
}

PtrToNode InitTree()
{
    PtrToNode P = (PtrToNode)malloc(sizeof(Node));

    strcpy(P->Array, "Multiple choice questions");
    P->FirstChild = NULL;
    P->NextSibling = (PtrToNode)malloc(sizeof(Node)); //mcq->NextSibling = fill

    strcpy(P->NextSibling->Array, "Fill in the blanks");
    P->NextSibling->FirstChild = NULL;
    P->NextSibling->NextSibling = NULL;
    //printf("done3\n");

    return P;
}

void MakePtrsToQues(int n, PtrToNode MCQArray[], int m, PtrToNode FILLArray[])
{
    for (int i = 0; i < n; i = i + 1)
        MCQArray[i] = MakeNode();

    for (int i = 0; i < n - 1; i = i + 1)
        MCQArray[i]->NextSibling = MCQArray[i + 1];

    for (int i = 0; i < m; i = i + 1)
        FILLArray[i] = MakeNode();

    for (int i = 0; i < m - 1; i = i + 1)
        FILLArray[i]->NextSibling = FILLArray[i + 1];

    // printf("done2\n");
}

PtrToNode ParseBank(FILE *fp)
{
    // PtrToNode MCQQuestionsAddress[NUMMCQ], FILLQuestionsAddress[NUMFILL];
    MakePtrsToQues(100, MCQQuestionsAddress, 100, FILLQuestionsAddress);

    PtrToNode Root = InitTree();
    PtrToNode Current_Q_Ptr;

    Root->FirstChild = MCQQuestionsAddress[0];
    Root->NextSibling->FirstChild = FILLQuestionsAddress[0];

    char A[300];
    char num[5];
    int x = -1, y = 1;
    NUMMCQ = 0;
    NUMFILL = 0;

    while (!feof(fp))
    {
        fgets(A, 300, fp);

        // printf("Done\n");
        if (A[0] == 'm')
        {
            // printf("DONE\n");
            for (;;)
            {
                fgets(A, 300, fp);

                if (A[0] == '~' && A[1] == 'm')
                    break;
                /* else if (A[0]=='/')
                {
                    NUMMCQ++;
                    printf("%d",NUMMCQ);
                }*/

                else if (A[0] == 'N')
                {
                    // printf("bbcj\n");
                    strcpy(num, &A[4]);
                    x = atoi(num);

                    Current_Q_Ptr = MCQQuestionsAddress[x - 1];
                    strcpy(Current_Q_Ptr->Array, &A[4]);
                    NUMMCQ++;
                }
                else if (A[0] == 'D')
                {
                    Current_Q_Ptr->FirstChild = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->Array, &A[4]);
                }
                else if (A[0] == 't')
                {
                    Current_Q_Ptr->FirstChild->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->Array, &A[4]);
                }
                else if (A[0] == 'O')
                {
                    Current_Q_Ptr->FirstChild->NextSibling->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->NextSibling->Array, &A[4]);
                }
                else if (A[0] == 'A')
                {
                    Current_Q_Ptr->FirstChild->NextSibling->NextSibling->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->NextSibling->NextSibling->Array, &A[4]);
                    if (x == NUMMCQ)
                    {
                        y = 0;
                    }
                }
            }
        }
        else if (A[0] == 'f')

        {
            for (;;)
            {
                fgets(A, 300, fp);

                if (A[0] == '~' && A[1] == 'f')
                    break;

                /*else if (A[0] == '/')
                    NUMFILL++;*/

                else if (A[0] == 'N')
                {
                    strcpy(num, &A[4]);
                    x = atoi(num);

                    Current_Q_Ptr = FILLQuestionsAddress[x - 1];
                    strcpy(Current_Q_Ptr->Array, &A[4]);
                    NUMFILL++;
                }
                else if (A[0] == 'D')
                {
                    Current_Q_Ptr->FirstChild = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->Array, &A[4]);
                }
                else if (A[0] == 't')
                {
                    Current_Q_Ptr->FirstChild->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->Array, &A[4]);
                }
                else if (A[0] == 'A')
                {
                    Current_Q_Ptr->FirstChild->NextSibling->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->NextSibling->Array, &A[4]);
                }
            }
        }
    }
    //printf("done4\n");
    return Root;
}

void MakeQuesPaperFile(PtrToNode Root)
{
    srand(time(0));
    FILE *fp[3];
        fp[0] = fopen("questionpaper1.txt", "w");
        fp[1] = fopen("questionpaper2.txt", "w");
        fp[2] = fopen("questionpaper3.txt", "w");
    for (int j = 0; j < 3; j++)
    {
        int i = 1;
        int q = 1;
        int flag[NUMMCQ];
        int pos;
        for (int count = 0; count < NUMMCQ; count++)
         flag[count] = 0;
        //printf("check\n");
        //printf("%d\n",NUMMCQ);

        pos = getkey(NUMMCQ, rand());
        //PtrToNode current_ques_ptr = Root->FirstChild;
        PtrToNode current_ques_ptr = MCQQuestionsAddress[pos];

        char A[300];
        //printf("check\n");
        float current_ques_difficulty;
        //printf("check\n");

        fprintf(fp[j], "%s\n\n", Root->Array);
        //printf("Check\n");
        while (current_ques_ptr && q <= NUMQ)
        {
            current_ques_difficulty = atof(current_ques_ptr->FirstChild->Array);

            if (current_ques_difficulty <= DQ[1] && current_ques_difficulty >= DQ[0])
            {

                fprintf(fp[j], "%d.", q);
                fprintf(fp[j], "%s", current_ques_ptr->FirstChild->NextSibling->Array);

                strcpy(A, current_ques_ptr->FirstChild->NextSibling->NextSibling->Array);

                fprintf(fp[j], "A.");
                for (i = 0; A[i] != '~'; i = i + 1)
                {
                    fprintf(fp[j], "%c", A[i]);
                }

                fprintf(fp[j], "\n");

                fprintf(fp[j], "B.");
                for (i = i + 1; A[i] != '~'; i = i + 1)
                {
                    fprintf(fp[j], "%c", A[i]);
                }

                fprintf(fp[j], "\n");

                fprintf(fp[j], "C.");
                for (i = i + 1; A[i] != '~'; i = i + 1)
                {
                    fprintf(fp[j], "%c", A[i]);
                }

                fprintf(fp[j], "\n");

                fprintf(fp[j], "D.");
                for (i = i + 1; A[i] != '~'; i = i + 1)
                {
                    fprintf(fp[j], "%c", A[i]);
                }

                fprintf(fp[j], "\n");
                fprintf(fp[j], "\n");
                q = q + 1;
            }
            flag[pos] = 1;
            pos = getkey(NUMMCQ, rand());
            while (flag[pos] != 0)
            {
                pos = getkey(NUMMCQ, rand());
            }
            current_ques_ptr = MCQQuestionsAddress[pos];
        }
        // printf("done5\n");
        // current_ques_ptr = Root->NextSibling->FirstChild;
        pos = getkey(NUMFILL, rand());
        current_ques_ptr = FILLQuestionsAddress[pos];
        int flag2[NUMFILL];
        for (int count = 0; count < NUMFILL; count++)
         flag2[count] = 0;

        q = 1;

        fprintf(fp[j], "\n%s\n\n", Root->NextSibling->Array);

        while (current_ques_ptr && q <= NUMF)
        {
            current_ques_difficulty = atof(current_ques_ptr->FirstChild->Array);

            if (current_ques_difficulty <= DF[1] && current_ques_difficulty >= DF[0])
            {
                fprintf(fp[j], "%d.", q);
                fprintf(fp[j], "%s", current_ques_ptr->FirstChild->NextSibling->Array);

                fprintf(fp[j], "\n");
                fprintf(fp[j], "\n");

                q = q + 1;
            }
            flag2[pos] = 1;
            pos = getkey(NUMFILL, rand());
            while (flag2[pos] != 0)
            {
                pos = getkey(NUMFILL, rand());
            }
            current_ques_ptr = FILLQuestionsAddress[pos];
        }
    }
    //  printf("done6\n");
}
int getkey(int n, int r)
{
    return r % n;
}