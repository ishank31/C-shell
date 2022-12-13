#include "headers.h"

void jobs(char* arg,int flag_r,int flag_s){
    for(int i=0;i<process_count;i++){
        if(process_count < 0){
            break;
        }
        char /*pid[200],*/path[200],status;
        
        int pid=process[i].pid;
        sprintf(path,"/proc/%d/stat",pid);

        
        int piid;
        char comm[100];

        if(process[i].stat == 'R' && flag_r == 1){
            printf("[%d] Running %s [%d]\n",i+1,process[i].name,process[i].pid);
        }
        else if(process[i].stat == 'T' && flag_s == 1){
            printf("[%d] Stopped %s [%d]\n",i+1,process[i].name,process[i].pid);
        }
        else if(flag_r == 0 && flag_s == 0){
            if(process[i].stat == 'R'){
                printf("[%d] Running %s [%d]\n",i+1,process[i].name,process[i].pid);
            }
            else{
                printf("[%d] Stopped %s [%d]\n",i+1,process[i].name,process[i].pid);
            }
        }
    }
}