//To assist other functions
#include "headers.h"

//To remove & in background process
void remove_amp(char *s)
{
    if (s == NULL)
    {
        return;
    }
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || '&')
        {
            continue;
        }
        else
        {
            s[i + 1] = '\0';
            break;
        }
    }
}


//To handle whitespaces in between
void remove_space(char* string){
    if(string==NULL){
        return;
    }
    int len = strlen(string),i,j;
    for(i=0; i<len; i++){
        if(string[0]==' '){
            for(i=0; i<(len-1); i++)
                string[i] = string[i+1];
                string[i] = '\0';
                len--;
                i = -1;
                continue;
        }
        if(string[i]==' ' && string[i+1]==' '){
            for(j=i; j<(len-1); j++){
                string[j] = string[j+1];
            }
            string[j] = '\0';
            len--;
            i--;
        }
    }
}
//To handle ; 
char** handle_delim(char** list,char* in){
    char* command;
    char* saveptr = in;
    command = strtok_r(in, ";", &saveptr);
    int i = 0;
    while(command != NULL)
    {
        list[i] = (char*)malloc(200* sizeof(char));
        strcpy(list[i++], command);
        command = strtok_r(NULL, ";", &saveptr);
    }
    return list;
}

//To trim string
void trim(char*s){
    if(s==NULL){
        return;
    }

    if(s[0]== '\n'){
        s[0]='\0';
        return;
    }

    for(int i=strlen(s)-1;i>=0;i--){
        if(s[i]==' ' || s[i]=='\n' || s[i]=='\t'){
            continue;
        }
        else{
            s[i+1]='\0';
            break;
        }
    }
    
}

//To handle leading whitespaces
void trimLeading(char * str)
{
    int index, i, j;
    index = 0;

    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }

    if(index != 0)
    {
        
        i = 0;
        while(str[i + index] != '\0')
        {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0'; 
    }
}

int argNum(const char *line) {
    
    if(line==NULL){
        return 0;
    }
    int stlen=0;
    if(line==NULL){
        line=NULL;
        stlen=0;
    }
    else{
        stlen=strlen(line);
    }
    char *tmp = (char*)calloc((stlen + 1) , sizeof(char));
    char *line_copy = (char*)calloc((stlen + 1) , sizeof(char));
    strcpy(line_copy, line);

    char *arg = strtok(line_copy, " ");
    int count = 0;

    while(arg != NULL) {
        count++;
        arg = strtok(NULL, " ");
    }


    free(tmp);
    free(line_copy);
    return count;
}
