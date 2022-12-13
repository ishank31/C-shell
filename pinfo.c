#include "headers.h"

//PINFO IMPLEMENTED
void p_info(char * arg,int flag_output){
    int arg_num = argNum(arg);
    if(arg_num == 0){
        pid_t pid = getpid();
        if(pid != 0){
            char path[400];
            sprintf(path, "/proc/%d/stat", pid);
            FILE *fp = fopen(path, "r");
            if(fp == NULL){
                printf("No such process exists\n");
                return;
            }
            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            char *token;
            char *saveptr;
            int i = 0;
            char* process_status=(char*) calloc(200, sizeof(char));
            char* memory=(char*) calloc(200, sizeof(char));
            while ((read = getline(&line, &len, fp)) != -1) {
                token = strtok_r(line, " ", &saveptr);
                while (token != NULL) {
                    if(i == 2){
                        strcpy(process_status, token);
                    
                    }
                    if(i == 22){
                        strcpy(memory, token);
                    
                    }
                    token = strtok_r(NULL, " ", &saveptr);
                    i++;
                }
            }

            sprintf(path, "/proc/%d/exe", pid);
            char *exe_path = (char *)calloc(200, sizeof(char));
            int path_len = readlink(path, exe_path, 200);
            exe_path[path_len] = '\0';

            
            printf("pid : %d\n", pid);
            printf("Process Status : %s\n", process_status);
            printf("memory : %s\n", memory);
            printf("Executable Path : %s\n", exe_path);

            free(process_status);
            free(memory);
            free(exe_path);
        }
        

    }
    else if(arg_num == 1){
        
        //get process status
        char path[400];
        sprintf(path, "/proc/%s/stat", arg);
        FILE *fp = fopen(path, "r");
        if(fp == NULL){
            printf("No such process exists\n");
            return;
        }
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        char *token;
        char *saveptr;
        int i = 0;
        char* process_status=(char*) calloc(200, sizeof(char));
        char* memory=(char*) calloc(200, sizeof(char));
        while ((read = getline(&line, &len, fp)) != -1) {
            token = strtok_r(line, " ", &saveptr);
            while (token != NULL) {
                if(i == 2){
                    strcpy(process_status, token);
                }
                if(i == 22){
                    strcpy(memory, token);
                }
                token = strtok_r(NULL, " ", &saveptr);
                i++;
            }
        }

        sprintf(path, "/proc/%s/exe", arg);
        char *exe_path = (char *)calloc(200, sizeof(char));
        int path_len = readlink(path, exe_path, 200);
        exe_path[path_len] = '\0';

        
        printf("pid : %s\n", arg);
        printf("Process Status : %s\n", process_status);
        printf("memory : %s\n", memory);
        printf("Executable Path : %s\n", exe_path);
        

        free(process_status);
        free(memory);
        free(exe_path);
    }
}