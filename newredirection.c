#include "headers.h"

void redirection(char *command, char *arg, int flag_input, int flag_output, int flag_doutput)
{
    if (flag_doutput == 1)
    {

        char *file = strtok(arg, ">>");
        char *file_name = strtok(NULL, ">>");
        // When no other arguments are passed, file should be used
        // Otherwise, file_name should be used as input
        if (file == NULL)
        {
            file = file_name;
        }
        if (strcmp(command, "echo") == 0 || strcmp(command, "ls") == 0)
        {
            file = file_name;
        }

        trimLeading(file);
        int fd = open(file, O_WRONLY | O_APPEND, 0644);
        if (fd < 0)
        {
            perror("Error in opening file");
            return;
        }
        int org;
        int org_fd;
        dup2(STDOUT_FILENO, org);
        dup2(STDOUT_FILENO, org_fd);
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("Error in duplicating file descriptor");
            return;
        }
        close(fd);

        if (strcmp(command, "echo") == 0)
        {
            echo(arg, flag_input, flag_output);
            dup2(org, STDOUT_FILENO);
            dup2(org_fd, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "pwd") == 0)
        {
            get_path(flag_output, arg);
            dup2(org, STDOUT_FILENO);
            dup2(org_fd, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "history") == 0)
        {
            history(flag_output, arg);
            dup2(org, STDOUT_FILENO);
            dup2(org_fd, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "pinfo") == 0)
        {
            p_info(arg, flag_output);
            dup2(org, STDOUT_FILENO);
            dup2(org_fd, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "ls") == 0)
        {
            trim(arg);
            exec_ls(arg);
            dup2(org, STDOUT_FILENO);
            dup2(org_fd, STDOUT_FILENO);
            return;
        }
        else
        { // all the other commands will be handled here
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("Error in forking child process");
            }

            if (pid == 0)
            {
                // In child process
                char *args[100];
                args[0] = command;
                args[1] = NULL;
                if (execvp(command, args) < 0)
                {
                    perror("Error in executing command");
                    return;
                }
                dup2(org_fd, STDOUT_FILENO);
            }
            else
            {
                // In parent process
                int status;
                waitpid(pid, &status, WUNTRACED);
                dup2(org_fd, STDOUT_FILENO);
                return;
            }
        }
    }
    else if (flag_input == 0 && flag_output == 1)
    {
        char *file = strtok(arg, ">");
        char *file_name = strtok(NULL, ">");
        // When no other arguments are passed, file should be used
        // Otherwise, file_name should be used as input
        if (file == NULL)
        {
            file = file_name;
        }
        if (strcmp(command, "echo") == 0 || strcmp(command, "ls") == 0)
        {
            file = file_name;
        }
        trimLeading(file);
        int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("Error in opening file");
            return;
        }
        int org;
        int org_fd_backup;
        dup2(STDOUT_FILENO, org_fd_backup);
        dup2(STDOUT_FILENO, org);
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
            perror("Error in duplicating file descriptor");
            return;
        }
        close(fd);

        if (strcmp(command, "echo") == 0)
        {
            echo(arg, flag_input, flag_output);
            dup2(org_fd_backup, STDOUT_FILENO);
            dup2(org, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "pwd") == 0)
        {
            get_path(flag_output, arg);
            dup2(org_fd_backup, STDOUT_FILENO);
            dup2(org, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "history") == 0)
        {
            history(flag_output, arg);
            dup2(org_fd_backup, STDOUT_FILENO);
            dup2(org, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "pinfo") == 0)
        {
            p_info(arg, flag_output);
            dup2(org_fd_backup, STDOUT_FILENO);
            dup2(org, STDOUT_FILENO);
            return;
        }
        else if (strcmp(command, "ls") == 0)
        {
            trim(arg);
            exec_ls(arg);
            dup2(org_fd_backup, STDOUT_FILENO);
            dup2(org, STDOUT_FILENO);
            return;
        }
        else
        { // all the other commands will be handled here
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("Error in forking child process");
            }

            if (pid == 0)
            {
                // In child process
                char *args[100];
                args[0] = command;
                args[1] = NULL;
                if (execvp(command, args) < 0)
                {
                    perror("Error in executing command");
                    return;
                }
                dup2(org_fd_backup, STDOUT_FILENO);
            }
            else
            {
                // In parent process
                int status;
                waitpid(pid, &status, WUNTRACED);
                dup2(org_fd_backup, STDOUT_FILENO);
                return;
            }
        }
    }
    else if (flag_input == 1 && flag_output == 0)
    {
    }
    else if (flag_input == 1 && flag_output == 1)
    {
    }
}
