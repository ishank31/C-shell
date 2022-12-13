//ECHO COMMAND IMPLEMENTED
#include "headers.h"

void echo(char* arg,int flag_input,int flag_output){
    if(arg == NULL){
        return;
    }

  
    remove_space(arg);
    printf("%s\n",arg);
    return;
}