#include"adt.h"

void Parseqp(FILE* q)
{
    char string[10];
    char type;
    char num[5];
    while(!feof(q))
    {
        fgets(string,10,q);
       // printf("Done\n");

        if(string[0]=='T')
        {
            //printf("done\n");
           type=string[4];
        }
        else if (string[0]=='N'&& type=='m')
        {
            strcpy(num,&string[4]);
            int x= atoi(num);
            NUMQ=x;
        }
        else if(string[0]=='N' && type=='f')
        {
            strcpy(num,&string[4]);
            int x=atoi(num);
            NUMF=x;
        }
        else if(string[0]=='D'&& type=='m')
        {
            strcpy(num,&string[5]);
            float x=atof(num);
            DQ=x;
        }
        else if(string[0]=='D'&& type=='f')
        {
            strcpy(num,&string[5]);
            float x=atof(num);
            DF=x;
        }
        
        

    }
    printf("%d %d\n",NUMQ,NUMF);
    printf("%f %f\n",DQ,DF);
}
