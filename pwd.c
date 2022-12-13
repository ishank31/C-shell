//PWD COMMAND IMPLEMENTED
#include "headers.h"

void get_path(int flag_output,char* arg){
    char* buff= (char*)calloc(250,sizeof(char));
    getcwd(buff,100);
  
    printf("%s\n",buff);
    free(buff);
}