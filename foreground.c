#include "headers.h"

int foreground(char* args[]){
    pid_t pid=fork();
    int stat,diff;
    if(pid == -1){ //When forking fails
        printf("Error: Process cannot be started\n");
        return -1;
    }  
    else if(pid == 0){
        // We are in child process
        if(execvp(args[0],args) < 0){ //When execvp fails
            return -1;
        }
    }
    else{
        fg_process.pid = pid;
        strcpy(fg_process.name,args[0]);
        pid_t waitp;
        // We are in parent process
        time_t st=time(NULL);
        //waitpid(pid,&stat,WUNTRACED);
        do{
            waitp=wait(&stat);
        }while(waitp != pid);
        time_t ed=time(NULL);
        diff=ed-st;
    }
    return diff;
}