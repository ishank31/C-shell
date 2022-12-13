#include "headers.h"

// This will be global
//  char* commands[20];
//  int ptr=0;

// history implemented
void history(int flag_output, char *arg)
{
    FILE *fp = fopen("history.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot display history");
    }
    else
    {
        char c = fgetc(fp);
        int i = 0;

        

        /*----------------STARTED HERE----------------------*/
        if (flag_output)
            if (ptr < 20)
            {
                while (c != EOF)
                {
                    printf("%c", c);
                    c = fgetc(fp);
                }
            }
            else
            {
                // print only last 10 commands of the file
                while (c != EOF)
                {
                    if (i >= ptr - 10)
                    {
                        printf("%c", c);
                    }
                    if (c == '\n')
                    {
                        i++;
                    }
                    c = fgetc(fp);
                }
            }
        /*-----------------ENDED-----------------*/
    }
    fclose(fp);
}

// write commands to history file
void write_history(char *command)
{
    FILE *fp;
    fp = fopen("history.txt", "w");

    if (ptr >= 20)
    {

        int i;
        for (i = 1; i <= 20; i++)
        {
            if (i == 20)
            {
                continue;
            }
            strcpy(commands[i - 1], commands[i]);
        }

        strcpy(commands[19], command);
        // ptr=0;
        // overwrite the file from the start
        fseek(fp, 0, SEEK_SET);

        for (int i = 0; i < 20; i++)
        {
            fprintf(fp, "%s", commands[i]);
        }
        ptr = 20;
    }
    else
    {
        strcpy(commands[ptr], command);

        for (int i = 0; i <= ptr; i++)
        {
            fprintf(fp, "%s", commands[i]);
        }

        ptr++;
        if (ptr > 20)
        {
            ptr = 20;
        }
    }

    fclose(fp);
}
