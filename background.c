#include "headers.h"

//int is_foreground;
//struct to store the background process info
// struct process_info{
//     pid_t pid;
//     char name[200];
// };

// //array of process_info
struct process_info process[100];
// int process_count = 0;

void delete_process(pid_t pid)
{
    if(pid == -1)
    {
        process_count=0;
        return;
    }
    int i;
    for (i = 0; i < process_count; i++)
    {
        if (process[i].pid == pid)
        {
            process[i].stat='T';
        }
    }
    // for (; i < process_count - 1; i++)
    // {
    //     process[i] = process[i + 1];
    // }
    // process_count--;
}

void process_completed(){
    if(is_foreground == 1){
        is_foreground = 0;
        return;
    }
    if(is_pipes == 1){
        is_pipes = 0;
        return;
    }
    int stat;
    pid_t pid=waitpid(-1,&stat,WNOHANG);
    if(pid < 0){
        printf("waitpid failed(check)\n");
    }

    for(int i=0;i<process_count;i++){
        int const exit_status=WEXITSTATUS(stat);
        if(WIFEXITED(exit_status) && process[i].pid == pid){
            if(exit_status == 0){
                printf("%s with pid= %d exited normally\n", process[i].name, pid);
            }
            else{
                printf("%s with pid= %d exited abnormally\n", process[i].name, pid);
            }
        }
        //display(*org_dir,time_span);
        delete_process(pid);
    }    
}

//Background process
void background(char* args[]){
    // remove_amp(args[1]);
    pid_t pid = fork();

    if(pid < 0 ){
        printf("Error in forking\n");
    }
    else if(pid == 0){
        if(execvp(args[0],args) < 0){
            printf("Error in executing command\n");
        }
        
    }
    else{
        printf("[%d] %d\n", process_count+1, pid);
        process[process_count].pid = pid;
        process[process_count].stat='R';
        strcpy(process[process_count].name,args[0]);
        process_count++;
    }
    
}
