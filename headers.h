#ifndef HEADERS_H
#define HEADERS_H

#include<stdio.h>
#include<sys/syscall.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<errno.h>
#include<sys/wait.h>
#include<signal.h>
#include<stddef.h>

//struct to store the background process info
typedef struct process_info{
    pid_t pid;
    char name[200];
    char stat;
}process_info;

//array of process_info
extern struct process_info process[100];
extern int process_count;

static char prev_dir[200];     //To store previous directory
static char org_dir[200];      //To store original directory

extern char* commands[20];     //To store commands for history command execution
extern int ptr;                //To store the index of commands array
extern int is_foreground;             //To check if the process is foreground or background
extern int is_pipes;                  //To check if the command has pipes
extern int org_pid; 
extern struct process_info fg_process; //To store the foreground process info

//Assignment-2 and Assignment-3
void remove_space(char* string);                        //To remove any whitespaces in between
char** handle_delim(char** list,char* in);              //To handle ;
void trim(char*s);                                      //To handle trailing whitespaces
int argNum(const char *line);                           //To get number of arguments
void exec_ls(char* arg);                                //To execute ls
int change_directory(char* arg,char* org_dir);          //To implement cd
void echo(char* arg,int flag_input,int flag_output);    //To implement echo
void get_path(int flag_output,char* arg);                                        //To implement pwd
int execCommand(char* command,char* arg,char* org_dir); //To compare commands
int input(char* org_dir);                               //To take input
void display(char* org_dir,int time_span);              //To display prompt
void history(int flag_output,char* arg);                                         //To display history
void write_history(char *command);                      //To store history 
int foreground(char* args[]);                           //To execute foreground process
void delete_process(pid_t pid);                         //To rearrange array after process is deleted
void process_completed();                               //To check if what process is completed
void background(char* args[]);                          //To execute background process
void remove_amp(char* arg);                             //To remove & from argument
void p_info(char *arg,int flag_output);                                 //To implement pinfo 
void disc(char* arg);                                   //To implement discover 
void redirection(char* command,char* arg,int flag_input,int flag_output,int flag_doutput); //To implement redirection
void jobs(char* arg,int flag_r,int flag_s);               //To implement jobs
void sig(char* arg);                                      //To implement sig
void fg(char* arg);                                       //To implement fg
void handle_ctrlc();                                      //To handle ctrl+c
void handle_ctrlz();                                      //To handle ctrl+z
void bg(char* arg);                                       //To implement bg

#endif