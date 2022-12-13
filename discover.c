#include "headers.h"

int all_1(const struct dirent *d)
{
    return 1;
}

int alphasort_without_case(const struct dirent **first, const struct dirent **second)
{
    return strcmp((*first)->d_name, (*second)->d_name);
}

void exec_disc(char* token,int flag_file,int flag_dir){
    struct stat st;
    stat(token, &st);

fflush(stdout);

    if( S_ISDIR(st.st_mode)){   
        printf("%s\n" ,token); //Printing the token that we received

        struct dirent **entry;
        DIR *dir = opendir(token);

        // Ensure we can open directory.
        if (dir == NULL)
        {
            printf("Cannot open directory\n");
            return;
        }
        struct stat statbuf;
        int file_num = scandir(token, &entry, all_1, alphasort_without_case);
        if(file_num > 0){
            for(int i=0;i<file_num;i++){
                struct stat is_dir;
                
                //Giving full path of the file
                char new_path[50];
                strcpy(new_path,token);
                strcat(new_path,"/");
                strcat(new_path,entry[i]->d_name);
                char c = entry[i]->d_name[0];
                
                stat(new_path, &is_dir);

                if(S_ISDIR(is_dir.st_mode) == 1 ){
                    if( flag_dir == 1){
                        if(c == '.'){
                            continue;
                        }
                        
                        exec_disc(new_path,flag_file,flag_dir);
                    }
                    
                }
                else{
                    if(S_ISREG(st.st_mode) && flag_file == 1){
                        printf("%s\n",entry[i]->d_name);
                    }
                }
            }
        }
        
        closedir(dir);
        return;
    }
    else{  //It is a file so print it directly
        printf("file stat is:%d" ,S_ISREG(st.st_mode));
        if(S_ISREG(st.st_mode) && flag_file == 1){
            printf("%s\n",token);
        }   
        
    }
    return;
}

void disc(char* arg){
    int flag_noarg=0;
    if(arg == NULL){
        flag_noarg=1;
    }
    int flag_file=0,flag_dir=0;
    int strl;
    if(arg ==NULL){
        strl=0;
    }
    else{
        strl = strlen(arg);
    }
    for(int i=0;i<strl;i++){
        if(arg[i == '-']){
            if(arg[i+1] == 'f'){
                flag_file = 1;
            }
            else if(arg[i+1] == 'd'){
                flag_dir = 1;
            }
        }
    }

    int count=0;
    if(flag_noarg || arg == NULL){
        flag_file=1;
        flag_dir=1;
        char cur_dirr[200];
        getcwd(cur_dirr,200);
        exec_disc(cur_dirr,flag_file,flag_dir);
    }
    else{
        char* token = strtok(arg," ");
        while(token != NULL){
            if(strcmp(token,"-f") == 0 || strcmp(token,"-d") == 0){   
                token=strtok(NULL," ");
                continue;
            }
            else{
                exec_disc(token,flag_file,flag_dir);
                count++;
                token = strtok(NULL," ");
            }

        }
        if(count == 0){
            exec_disc(org_dir,flag_file,flag_dir);
        }
    }
}
