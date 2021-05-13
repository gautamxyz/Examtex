#include "ast.h"
#include <time.h>
PtrToNode MCQQuestionsAddress[100], FILLQuestionsAddress[100];

void Parseqp(FILE *q) //function to parse the input question paper file
{
    char string[10];
    char type;
    char num[5];
    NUMQ=0;
    NUMF=0;
    while (!feof(q))
    {
        fgets(string, 10, q);

        if (string[0] == 'T')
        {
            type = string[4]; //type = m or f
        }
        else if (string[0] == 'N' && type == 'm')
        {
            strcpy(num, &string[4]);
            int x = atoi(num);
            /*if (x > NUMMCQ || x < 1)
            {
                printf("Error invalid number of MCQ Questions!\n");
                FILE *fp[3];
                fp[0] = fopen("questionpaper1.md", "w");
                fp[1] = fopen("questionpaper2.md", "w");
                fp[2] = fopen("questionpaper3.md", "w");
                for (int i = 0; i < 3; i++)
                {
                    fprintf(fp[i], "%s", "ERROR!");
                }
                exit(0);
            }*/
            NUMQ = x; //NUMQ stores the number of MCQ questions as per the input question paper file
        }
        else if (string[0] == 'N' && type == 'f')
        {
            strcpy(num, &string[4]);
            int x = atoi(num);
            /*if (x > NUMFILL || x < 1)
            {
                printf("Error invalid number of Fill in the blanks Questions!\n");
                FILE *fp[3];
                fp[0] = fopen("questionpaper1.txt", "w");
                fp[1] = fopen("questionpaper2.txt", "w");
                fp[2] = fopen("questionpaper3.txt", "w");
                for (int i = 0; i < 3; i++)
                {
                    fprintf(fp[i], "%s", "ERROR!");
                }
                exit(0);
            }*/
            NUMF = x; //NUMF stores the number of FILL IN THE BLANK questions as per the input question paper file
        }
        else if (string[0] == 'D' && type == 'm')
        {
            strcpy(num, &string[5]);
            float x = atof(num);
            if (x > 1 || x < 0)
            {
                printf("Error! Difficulty out of range!\n");
                FILE *fp[3];
                fp[0] = fopen("questionpaper1.md", "w");
                fp[1] = fopen("questionpaper2.md", "w");
                fp[2] = fopen("questionpaper3.md", "w");
                for (int i = 0; i < 3; i++)
                {
                    fprintf(fp[i], "%s", "ERROR!");
                }
                exit(0);
            }
            if (string[2] == '<')
                DQ[1] = x; //DQ[1] = Upper limit for difficulty of MCQ questions
            else if (string[2] == '>')
                DQ[0] = x; //DQ[0] = Lower limit for difficulty of MCQ questions
        }
        else if (string[0] == 'D' && type == 'f')
        {
            strcpy(num, &string[5]);
            float x = atof(num);
            if (x > 1 || x < 0)
            {
                printf("Error! Difficulty out of range!\n");
                FILE *fp[3];
                fp[0] = fopen("questionpaper1.md", "w");
                fp[1] = fopen("questionpaper2.md", "w");
                fp[2] = fopen("questionpaper3.md", "w");
                for (int i = 0; i < 3; i++)
                {
                    fprintf(fp[i], "%s", "ERROR!");
                }
                exit(0);
            }
            if (string[2] == '<')
                DF[1] = x; //DF[1] = Upper limit for difficulty of FIB questions
            else if (string[2] == '>')
                DF[0] = x; //DF[0] =Lower limit for difficulty of FIB questions
        }
        else if ((string[0] != '/' && string[1] != 's') && (string[0] != '~' && string[1] != 's'))
        {
            printf("%s\n", string);
            printf("Error! Invalid Syntax!\n");
            FILE *fp[3];
            fp[0] = fopen("questionpaper1.md", "w");
            fp[1] = fopen("questionpaper2.md", "w");
            fp[2] = fopen("questionpaper3.md", "w");
            for (int i = 0; i < 3; i++)
            {
                fprintf(fp[i], "%s", "ERROR!");
            }
            exit(0);
        }
    }

    if (DF[1] < DF[0] || DQ[1] < DQ[0])
    {
        printf("Error! Invalid Difficulty!\n");
        FILE *fp[3];
        fp[0] = fopen("questionpaper1.md", "w");
        fp[1] = fopen("questionpaper2.md", "w");
        fp[2] = fopen("questionpaper3.md", "w");
        for (int i = 0; i < 3; i++)
        {
            fprintf(fp[i], "%s", "ERROR!");
        }
        exit(0);
    }
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

    strcpy(P->Array, "Multiple choice questions"); //Root = mcq
    P->FirstChild = NULL;
    P->NextSibling = (PtrToNode)malloc(sizeof(Node));

    strcpy(P->NextSibling->Array, "Fill in the blanks"); //mcq->NextSibling = fill
    P->NextSibling->FirstChild = NULL;
    P->NextSibling->NextSibling = NULL;

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
}

PtrToNode ParseBank(FILE *fp) //Function to parse questionbank file into ast
{
    MakePtrsToQues(100, MCQQuestionsAddress, 100, FILLQuestionsAddress);

    PtrToNode Root = InitTree();
    PtrToNode Current_Q_Ptr;

    Root->FirstChild = MCQQuestionsAddress[0];               //Root->Firstchild = first mcq question in the question bank
    Root->NextSibling->FirstChild = FILLQuestionsAddress[0]; //Root->NextSibling->Firstchild = first fill question in the question bank

    char A[500];
    char num[5];
    int x = -1;
    NUMMCQ = 0;
    NUMFILL = 0;

    while (!feof(fp))
    {
        fgets(A, 500, fp);

        if (A[0] == 'm') //type = mcq (starts parsing the mcq section)
        {
            for (;;)
            {
                fgets(A, 500, fp);

                if (A[0] == '~' && A[1] == 'm') //~mcq indicates end of mcq section in the question bank
                    break;

                else if (A[0] == 'N')
                {
                    strcpy(num, &A[4]);
                    x = atoi(num);

                    Current_Q_Ptr = MCQQuestionsAddress[x - 1];
                    strcpy(Current_Q_Ptr->Array, &A[4]); //Current_Q_ptr->Array now stores the question no.
                    NUMMCQ++;
                }
                else if (A[0] == 'D')
                {
                    Current_Q_Ptr->FirstChild = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->Array, &A[4]); //Current_Q_Ptr->FirstChild->Array stores difficulty value
                }
                else if (A[0] == 't')
                {
                    Current_Q_Ptr->FirstChild->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->Array, &A[4]); //Current_Q_Ptr->FirstChild->NextSibling->Array stores text of the question
                }
                else if (A[0] == 'O')
                {
                    Current_Q_Ptr->FirstChild->NextSibling->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->NextSibling->Array, &A[4]); //Current_Q_Ptr->FirstChild->NextSibling->NextSibling->Array stores the options
                }
                else if (A[0] == 'A')
                {
                    Current_Q_Ptr->FirstChild->NextSibling->NextSibling->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->NextSibling->NextSibling->Array, &A[4]); //Current_Q_Ptr->FirstChild->NextSibling->NextSibling->NextSibling->Array stores the answer
                }
                else if (A[0] != '/' && A[1] != 'q')
                {
                    printf("%s\n", A);
                    printf("Error! Invalid Syntax!\n");
                    FILE *fp[3];
                    fp[0] = fopen("questionpaper1.md", "w");
                    fp[1] = fopen("questionpaper2.md", "w");
                    fp[2] = fopen("questionpaper3.md", "w");
                    for (int i = 0; i < 3; i++)
                    {
                        fprintf(fp[i], "%s", "ERROR!");
                    }
                    exit(0);
                }
            }
        }
        else if (A[0] == 'f') //type = mcq (starts parsing the fill in the blanks section)

        {
            for (;;)
            {
                fgets(A, 500, fp);

                if (A[0] == '~' && A[1] == 'f') //~fill indicates end of fill questions
                    break;

                /*else if (A[0] == '/')
                    NUMFILL++;*/

                else if (A[0] == 'N')
                {
                    strcpy(num, &A[4]);
                    x = atoi(num);

                    Current_Q_Ptr = FILLQuestionsAddress[x - 1];
                    strcpy(Current_Q_Ptr->Array, &A[4]); // Current_Q_Ptr->Array stores question number
                    NUMFILL++;
                }
                else if (A[0] == 'D')
                {
                    Current_Q_Ptr->FirstChild = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->Array, &A[4]); // Current_Q_Ptr->FirstChild->Array stores  difficulty
                }
                else if (A[0] == 't')
                {
                    Current_Q_Ptr->FirstChild->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->Array, &A[4]); // Current_Q_Ptr->FirstChild->NextSibling->Array stores text of the question
                }
                else if (A[0] == 'A')
                {
                    Current_Q_Ptr->FirstChild->NextSibling->NextSibling = MakeNode();
                    strcpy(Current_Q_Ptr->FirstChild->NextSibling->NextSibling->Array, &A[4]); //Current_Q_Ptr->FirstChild->NextSibling->NextSibling->Array stores the answer
                }
            }
        }
    }
    return Root;
}

void MakeQuesPaperFile(PtrToNode Root) //Function to output three different question paper files
{
    srand(time(0));
    FILE *fp[3];
    fp[0] = fopen("questionpaper1.md", "w"); //output file 1
    fp[1] = fopen("questionpaper2.md", "w"); //output file 2
    fp[2] = fopen("questionpaper3.md", "w"); //output file 3
    for (int j = 0; j < 3; j++)
    {
        int i = 1;
        int q = 1;
        int flag[NUMMCQ];//keeps track of questions already used or questions that don't match the required difficulty

        int pos;
        int check = 1, check2 = 0;
        for (int count = 0; count < NUMMCQ; count++)
            flag[count] = 0; 
        pos = getkey(NUMMCQ, rand()); //selects a random question under mcq section 

        PtrToNode current_ques_ptr = MCQQuestionsAddress[pos]; //PtrToNode current_ques_ptr = Root->FirstChild;

        char A[500];
        float current_ques_difficulty;

        char *token;
        if(NUMQ!=0)
        fprintf(fp[j], "# %s\n\n", Root->Array); //prints "MULTIPLE CHOICE QUESTIONS"

        while (current_ques_ptr && q <= NUMQ)
        {
            current_ques_difficulty = atof(current_ques_ptr->FirstChild->Array);
            flag[pos] = 1;

            if (current_ques_difficulty <= DQ[1] && current_ques_difficulty >= DQ[0]) //checks whether the difficulty of the question is within required range
            {

                fprintf(fp[j], "%d. ", q);
                fprintf(fp[j], "%s", current_ques_ptr->FirstChild->NextSibling->Array); //current_ques_ptr->FirstChild->NextSibling->Array stores text
                fprintf(fp[j], "\n");

                strcpy(A, current_ques_ptr->FirstChild->NextSibling->NextSibling->Array); //current_ques_ptr->FirstChild->NextSibling->NextSibling->Array stores options

                char str[8][100]; //each str[i] will store an option
                strcpy(str[0], current_ques_ptr->FirstChild->NextSibling->NextSibling->NextSibling->Array); //FirstChild->NextSibling->NextSibling->NextSibling->Array stores the answer

                token = strtok(A, "~"); //options are separated by ~ in the question bank
                int i = 1;
                int option;
                while (token != NULL)
                {
                    strcpy(str[i], token); //parsing the options into separate strings
                    i++;
                    token = strtok(NULL, "~");
                }
                int taken[8] = {0}; //keeps track of options already used
                int p = getkey(4, rand()); //selects a random position for the answer among the four options
                p++;
                taken[0] = 1; //  str[0] (the answer) has been chosen
                for (i = 1; i <= 4; i++)
                {
                    if (i == p)
                    {
                        fprintf(fp[j], "\t%c. %s\n", 64 + i, str[0]); //outputs the answer as the pth option
                        //  fprintf(fp[j], "\n");
                    }
                    else
                    {
                        option = getkey(8, rand());
                        while (taken[option] != 0 ) //choose an option not already taken
                            option = getkey(8, rand());
                        fprintf(fp[j], "\t%c. %s\n", 64 + i, str[option]); //str[option] has been chosen
                        fprintf(fp[j], "\n");
                        taken[option] = 1;
                    }
                }
                //fprintf(fp[j], "\n");
                fprintf(fp[j], "\n");

                q = q + 1;
            }
            //flag[pos] = 1;
            pos = getkey(NUMMCQ, rand());
            while (flag[pos] != 0)//choose a question that's not already taken
            {
                pos = getkey(NUMMCQ, rand());
            }
            for (int cx = 0; cx < NUMMCQ; cx++)
            {
                if (flag[cx] == 1)
                {
                    check++;
                }
                if (check == NUMMCQ && q < NUMQ)
                {
                    printf("Error! Not sufficient number of questions!\n");
                    FILE *qs[3];
                    fclose(fp[0]);
                    fclose(fp[1]);
                    fclose(fp[2]);
                    qs[0] = fopen("questionpaper1.md", "w");
                    qs[1] = fopen("questionpaper2.md", "w");
                    qs[2] = fopen("questionpaper3.md", "w");
                    for (int i = 0; i < 3; i++)
                    {
                        fprintf(qs[i], "%s", "ERROR!");
                    }
                    exit(0);
                }
                else if (check == NUMMCQ && q == NUMQ)
                {
                    check2 = 1;
                }
            }
            check = 1;
            if (check2 == 1)
            {
                break;
            }

            current_ques_ptr = MCQQuestionsAddress[pos];
        }
        pos = getkey(NUMFILL, rand());//selects a random question under fill in the blanks section 
        current_ques_ptr = FILLQuestionsAddress[pos]; // current_ques_ptr = Root->NextSibling->FirstChild;
        int flag2[NUMFILL];//keeps track of questions already used or questions that don't match the required difficulty
        for (int count = 0; count < NUMFILL; count++)
            flag2[count] = 0;

        check = 1;
        check2 = 0;
        q = 1;
        if(NUMF!=0)
        fprintf(fp[j], "\n# %s\n\n", Root->NextSibling->Array); //prints "FILL IN THE BLANKS"

        while (current_ques_ptr && q <= NUMF)
        {
            flag2[pos] = 1;
            current_ques_difficulty = atof(current_ques_ptr->FirstChild->Array); //current_ques_ptr->FirstChild->Array stores difficulty

            if (current_ques_difficulty <= DF[1] && current_ques_difficulty >= DF[0]) //checks whether difficulty is within required range
            {
                fprintf(fp[j], "%d. ", q);
                fprintf(fp[j], "%s", current_ques_ptr->FirstChild->NextSibling->Array); //current_ques_ptr->FirstChild->NextSibling->Array stores text

                fprintf(fp[j], "\n");
                fprintf(fp[j], "\n");

                q = q + 1;
            }
            //flag2[pos] = 1;
            pos = getkey(NUMFILL, rand());
            while (flag2[pos] != 0)//choose a question that's not already taken
            {
                pos = getkey(NUMFILL, rand());
            }
            for (int cx = 0; cx < NUMFILL; cx++)
            {
                if (flag2[cx] == 1)
                {
                    check++;
                }
                if (check == NUMFILL && q < NUMF)
                {
                    printf("Error! Not sufficient number of questions!\n");
                    FILE *qs[3];
                    fclose(fp[0]);
                    fclose(fp[1]);
                    fclose(fp[2]);
                    qs[0] = fopen("questionpaper1.md", "w");
                    qs[1] = fopen("questionpaper2.md", "w");
                    qs[2] = fopen("questionpaper3.md", "w");
                    for (int i = 0; i < 3; i++)
                    {
                        fprintf(qs[i], "%s", "ERROR!");
                    }
                    exit(0);
                }
                else if (check == NUMFILL && q == NUMF)
                {
                    check2 = 1;
                }
            }
            if (check2 == 1)
            {
                break;
            }

            check = 1;
            current_ques_ptr = FILLQuestionsAddress[pos];
        }
    }
}
int getkey(int n, int r)
{
    return r % n;
}
