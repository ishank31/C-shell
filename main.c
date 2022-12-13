#include "headers.h"

char *commands[20];
int ptr = 0;
int is_foreground;
int is_pipes;
int org_pid;
int process_count;

int main()
{
    is_foreground=0;
    is_pipes=0;
    process_count = 0;
    ptr = 0;
    for (int i = 0; i < 20; i++)
    {
        commands[i] = (char *)calloc(200, sizeof(char));
    }
    // reading the history file and updating the commands array and ptr
    FILE *fp = fopen("history.txt", "r");

    char cmd[200];
    int i = 0;
    while (fgets(cmd, 200, fp) != NULL && i < 20)
    {
        strcpy(commands[i], cmd);
        i++;
        ptr++;
    }
    
    fclose(fp);
    prev_dir[0] = '\0';
    char buff[200];
    strcpy(org_dir, getcwd(buff, 200));
    org_pid=getpid();

    int exit = 1;
    do
    {
        //signal(SIGCHLD, process_completed);
        display(org_dir, exit);
        exit = input(org_dir);
    } while (exit >= 1 || exit == -1);

    for(int i=0;i<20;i++){
        free(commands[i]);
    }

    return 0;
}