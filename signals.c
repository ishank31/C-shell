#include "headers.h"

void handle_ctrlc(){
    pid_t pid = getpid();
    
    if(fg_process.pid != 1){
        kill(fg_process.pid,SIGINT);
        return;
    }
    else {
        display(org_dir,0);
        fflush(stdout);    
    }
    display(org_dir,0);
    return;
}

void handle_ctrlz(){
    pid_t pid = getpid();
    if(fg_process.pid != -1){
        kill(fg_process.pid, SIGTTIN);
        kill(fg_process.pid, SIGTSTP);

        strcpy(process[process_count].name,fg_process.name);
        process[process_count].pid=fg_process.pid;
        process_count++;
    }
}