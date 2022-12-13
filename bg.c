#include "headers.h"

void bg(char * arg){
    trim(arg);
    trimLeading(arg);
    int process_num=atoi(arg)-1;

    if(process_count < process_num+1 || process_num < 0){
        printf("No such process exists\n");
        return;
    }

    pid_t pid=process[process_num].pid;
    char path[200];
    sprintf(path,"/proc/%d/stat",pid);
    FILE* fd=fopen(path,"r");
    if(fd == NULL){
        perror("Not able to open the file\n");
        return;
    }
    else{
        kill(pid,SIGCONT);
        kill(pid,SIGTTIN);
    }

}