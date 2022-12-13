//CD IMPLEMENTED
#include "headers.h"

int change_directory(char* arg,char* org_dir){
    int arg_num = argNum(arg);
    
    if(arg_num>1){
        perror("Too many arguments");
        
    }
    char* path=(char*) calloc(200,sizeof(char));
    
    if(arg_num==0){        //If only cd is given by user
        
        strcpy(path,org_dir);
    }
    else if(strcmp(arg,".")==0){    //for cd .
        char*temp=(char*) calloc(200,sizeof(char));
        getcwd(temp,200);
        strcpy(path,temp);
        free(temp);
    }
     else if(strcmp(arg,"..")==0){   //for cd ..
        char* temp=(char*) calloc(200,sizeof(char));
        getcwd(temp,200);
        
        for(int i=strlen(temp)-1;i>=0;i--){
            if(temp[i]=='/'){
                temp[i]='\0';
                break;
            }
        }
        
        strcpy(path,temp);
    }
    else if(strcmp(arg,"-")==0){
        if(prev_dir[0]=='\0'){
            printf("Old directory not set");
        }
        else{
            printf("%s\n" ,prev_dir);
            strcpy(path,prev_dir);

            char current[200];
            getcwd(current,200);
            char temp[200];
        }

    }
    else if(strcmp(arg,"~")==0){    //for cd ~
        strcpy(path,org_dir);
    }
    else if(arg_num==1){
        
        char curdir[200];
        getcwd(curdir,200);
        char ch='/';
        char s[200];
        strcpy(s,curdir);
        strncat(s,&ch,1);
        strncat(s,arg,strlen(arg));
        
        strcpy(path,s);
        
    }
    else{
        printf("Error:cd %s command not found\n",arg);
    }
    char previous[200];
    getcwd(previous,200);
    strcpy(prev_dir,previous);
    trim(path);
    int check=chdir(path);    

    if(check==-1){
        perror("There was an error in changing directory");
        
    }
    return 1;
}