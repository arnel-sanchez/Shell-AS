// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // // //
//  VARIABLES LIBRARY:  //
// // // // // // // // //

#include "variables.h"

variables **variable=NULL;

void set(history *hist, linked_jobs *jobs, int *pid, char **tokens)
{
    if(tokens[1] == NULL)
    {
        if (variable == NULL)
            return;
        int i = 0;
        while (variable[i] != NULL && variable[i]->var != NULL) {
            if(variable[i]->value != NULL) {
                printf("%s", variable[i]->var[0]);
                printf("=");
                int k = 0;
                while (variable[i] != NULL && variable[i]->value[k] != NULL) {
                    printf("%s", variable[i]->value[k]);
                    printf(" ");
                    k++;
                }
                if(k==0)
                    printf("NULL");
                printf("\n");
            }
            i++;
        }
    }
    else
    {
        if(variable==NULL)
        {
            variable=(variables**)calloc(2, sizeof(variables*));
        }
        int i=0;
        int exist=0;
        while(variable[i]!=NULL)
        {
            if(!strcmp(variable[i]->var[0], tokens[1]))
            {
                exist=1;
                break;
            }
            i++;
        }
        if(!exist) {
            variable[i] = NULL;
            variable[i] = (variables *)calloc(1024, sizeof(variables));
            variable[i]->var = NULL;
            variable[i]->var = (char **) calloc(1024, sizeof(char *));
            variable[i]->var[0] = tokens[1];
        }
        variable[i]->value = NULL;
        variable[i]->value = (char **) calloc(1024, sizeof(char *));
        int k=0;
        int inicio=0;
        char *to_execute=(char *)calloc(1024, sizeof(char));
        to_execute[0] = 0;
        int p=0;
        int m=0;
        while (tokens[k]!=NULL)
        {
            if(tokens[k][p]=='`' && !inicio)
            {
                inicio=1;
                p++;
            }
            else if(tokens[k][p]=='`' && inicio)
            {
                break;
            }
            else if(tokens[k][p]==0)
            {
                to_execute[m]=' ';
                m++;
                k++;
                p=0;
            }
            else if(inicio)
            {
                to_execute[m]=tokens[k][p];
                p++;
                m++;
            } else
            {
                k++;
            }
        }
        to_execute[m++]=' ';
        to_execute[m++]='>';
        to_execute[m++]=' ';
        to_execute[m++]='a';
        to_execute[m++]='q';
        to_execute[m++]='w';
        to_execute[m++]='e';
        to_execute[m++]='r';
        to_execute[m++]='s';
        to_execute[m++]='d';
        to_execute[m++]='f';
        to_execute[m++]='s';
        to_execute[m++]='c';
        to_execute[m++]='v';
        to_execute[m++]='g';
        to_execute[m++]='g';
        to_execute[m++]='u';
        to_execute[m++]='u';
        to_execute[m++]='a';
        to_execute[m++]='.';
        to_execute[m++]='t';
        to_execute[m++]='x';
        to_execute[m++]='t';
        to_execute[m]=0;

        tokens++;
        tokens++;
        if(to_execute[0]==' ')
            variable[i]->value=tokens;
        else
        {
            counters count = create_counter();
            command *commands = tokenize(hist, 0, to_execute, &count, 0);
            int status = 0;
            control(hist, commands, count, 0, jobs, pid, &status);
            int file_descriptor = open("aqwersdfscvgguua.txt", O_RDONLY);
            char **line=(char**)calloc(1024, sizeof(char*));
            line[0]=(char*)calloc(1024, sizeof(char));
            char c;
            k=0;
            m=0;
            int l=read(file_descriptor,&c,1);
            for (int j = 0; l != 0; ++j)
            {
                if(c!='\n')
                {
                    line[k][m]=c;
                    m++;
                }
                else
                {
                    k++;
                    m=0;
                    line[k]=(char*)calloc(1024, sizeof(char));
                }
                l=read(file_descriptor,&c,1);
            }
            k=0;
            m=0;
            while (line[m]!=NULL)
            {
                if(strcmp(line[m],"aqwersdfscvgguua.txt") != 0)
                {
                    variable[i]->value[k]=line[m];
                    k++;
                }
                m++;
            }
            close(file_descriptor);
            remove("aqwersdfscvgguua.txt");
        }
    }
}

void get(char **tokens)
{
    if(tokens[1]==NULL)
        return;
    else
    {
        int i=0;
        tokens++;
        while(variable[i]!=NULL && variable[i]->var != NULL)
        {
            if(*tokens!=NULL && !strcmp(variable[i]->var[0],*tokens) && variable[i]->value!=NULL)
            {
                int j=0;
                while(variable[i]->value[j] != NULL)
                {
                    printf("%s", variable[i]->value[j]);
                    printf(" ");
                    j++;
                }
                if(j==0)
                    printf("NULL");
                printf("\n");
                tokens++;
            }
            i++;
        }
    }
}

void unset(char **tokens)
{
    if(variable == NULL || tokens[1] == NULL)
        return;
    int i=0;
    tokens++;
    while(variable[i] != NULL && variable[i]->var != NULL)
    {
        if(*tokens != NULL && !strcmp(variable[i]->var[0], *tokens))
        {
            variable[i]->value = NULL;
            tokens++;
        }
        i++;
    }
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
