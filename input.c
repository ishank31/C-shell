//To take the input string and pass it to respective functions
#include "headers.h"

int execCommand(char *command, char *arg, char *org_dir)
{
    trim(arg);
    int amp_status=0,flag_input=0,flag_output=0,flag_pipe=0,flag_doutput=0; //To check if it is a background process
    int flag_r=0,flag_s=0;
    if(arg != NULL){
        if(arg[strlen(arg)-1]=='&'){
            amp_status=1;
            arg[strlen(arg)-1]='\0';
        }
    }

    if(arg != NULL){
        for(int i=0;i<strlen(arg);i++){
            if(arg[i]=='<'){   //checking for input redirection
                flag_input=1;
            }
            if(arg[i]=='>'){   //checking for output redirection
                flag_output=1;
                if(arg[i+1]=='>'){
                    flag_doutput=1;
                }
            }
            if(arg[i]== '|'){   //cheking for pipe
                flag_pipe=1; 
            }
            if(arg[i] == '-'){    //chekcing for jobs
                if(arg[i+1] == 'r'){
                    flag_r = 1;
                }
                else if(arg[i+1] == 's'){
                    flag_s = 1;
                }
            }
        }
    }
    
    
    if (strcmp(command, "cd") == 0)
    {
        trim(arg);
        change_directory(arg, org_dir);
        return 1;
    }
    
    else if(flag_input==1 || flag_output==1){   //handling only input and output redirection
        redirection(command,arg,flag_input,flag_output,flag_doutput);
        return 1;

    }
    else if(strcmp(command,"fg")==0){
        fg(arg);
        return 1;
    }
    else if(strcmp(command,"jobs")==0){
        jobs(arg,flag_r,flag_s);
        return 1;
    }
    else if(strcmp(command,"sig")==0){
        sig(arg);
        return 1;
    }
    else if (strcmp(command, "echo") == 0)
    {
        echo(arg,flag_input,flag_output);
        return 1;
    }
    else if (strcmp(command, "pwd") == 0)
    {
        get_path(flag_output,arg);
        return 1;
    }
    else if (strcmp(command, "ls") == 0)
    {
        trim(arg);
        exec_ls(arg);
        return 1;
    }
    else if (strcmp(command, "exit") == 0)
    {
        return 0;
    }
    else if (strlen(command) == 0 || command == NULL)
    {
        return 1;
    }
    else if (strcmp(command, "history") == 0){
        history(flag_output,arg);
        return 1;
    }
    else if(strcmp(command, "pinfo") == 0){
        p_info(arg,flag_output);
        return 1;
    }
    else if(strcmp(command,"discover") == 0){
        disc(arg);
        return 1;
    }
    else if(amp_status == 1){
        char* to_background[100];
        to_background[0]=command;
        remove_amp(arg);
        to_background[1]=arg;
        
        background(to_background);
        return 1;
    }
    else
    {
        is_foreground=1;
        char* to_foreground[100];
        to_foreground[0]=command;
        to_foreground[1]=arg;
        
        int foreground_check=foreground(to_foreground);
        is_foreground=0;
        // if(foreground_check < 0){
        //     printf("Error: %s command not found\n", command);
        //     is_foreground=0;
        // }
  
        return foreground_check;
    }
}

int input(char* org_dir){
    char *in=(char*) calloc(100,sizeof(char));
    fgets(in,100,stdin);
    
    
     //Takes input of the command with spaces
    write_history(in);

    //Check if there exists a ; or not
    char** list = (char**)calloc(50, sizeof(char));
    char** list_collec=handle_delim(list,in);
    
    int count=0;
    for(int i=0;list_collec[i]!=NULL;i++){
        count++;
    }

    int ret;
    for(int i=0;/*list_collec[i]!=NULL*/i<count;i++){
        char* command=strtok(list[i], " "); //Extracts the command from the command with arguments

        trim(command);
        char* arg=strtok(NULL,"");
    
        ret=execCommand(command,arg,org_dir);    //Here the command will actually be implemented
    }

    
    free(in);
    return ret;
}
