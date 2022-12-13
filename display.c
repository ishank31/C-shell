#include "headers.h"

void display(char* org_dir, int time_span){
    
    // char* check=strstr(org_dir,curr_dir); //checking if curr_dir exists in org_dir

    char* user_name=getlogin(); //getting username
    char host[200];
    gethostname(host,200);     //getting hostname
    char dir[200];
    char* curr_dir=getcwd(dir,200);   //getting current directory
    
    
    if(strcmp(curr_dir,org_dir)==0){
        curr_dir=" ";
    }
    else if(strlen(curr_dir)<strlen(org_dir)){
        
    }
    else{
        char* trim_name=(char*) calloc(200,sizeof(char));
        int i,j;
        for(i=strlen(org_dir),j=0;i<strlen(curr_dir);i++,j++){
            trim_name[j]=curr_dir[i];
        }
        strcpy(curr_dir,trim_name);
    }
    
    signal(SIGINT, handle_ctrlc);
    signal(SIGCHLD, process_completed);
    
    //signal(SIGTSTP,handle_ctrlz);
    if(time_span > 1){
        printf("\033[1;31m<%s@%s:~\033[0m" "\033[1;33m%s\033[0m" "\033[1;31m took %ds>\033[0m", user_name, host, curr_dir,time_span);
    }
    else{
        printf("\033[1;31m<%s@%s:~\033[0m\033[1;33m%s\033[0m\033[1;31m>\033[0m", user_name, host, curr_dir);
    }
    
}