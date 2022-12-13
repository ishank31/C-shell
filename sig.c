#include "headers.h"

void sig(char *arg)
{
    int process_num,signal_num;
    if (arg != NULL)
    {
        char *num = strtok(arg, " ");
        process_num = atoi(num);

        char *signal = strtok(NULL, " ");
        signal_num = atoi(signal);
    }
    else{
        printf("Enter valid arguments\n");
        return;
    }

    char *remaining = strtok(NULL, " ");
    if (remaining != NULL)
    {
        printf("Too many arguments\n");
        return;
    }

    if (process_num > 0 && process_num <= process_count)
    {
        kill(process[process_num - 1].pid, signal_num);
    }
    else
    {
        printf("Invalid process number\n");
    }
}