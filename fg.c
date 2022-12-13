#include "headers.h"
struct process_info fg_process;

void fg(char* arg){
    trim(arg);
    trimLeading(arg);
    int process_num=atoi(arg)-1;

    char path[200];
    int pid=process[process_num].pid;

    sprintf(path,"/proc/%d/stat",pid);
    FILE* fd=fopen(path,"r");
    if(fd == NULL){
        perror("Not able to open the file\n");
        return;
    }   

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, process[process_num].pid);

    //adding to foreground process struct
    strcpy(fg_process.name, process[process_num].name);
    fg_process.pid = process[process_num].pid;

    // making process go to foreground
    kill(process[process_num].pid, SIGCONT);
    // back_process[back_process_num].process_num = -1;
    waitpid(-1, NULL, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    fg_process.pid = -1;
}