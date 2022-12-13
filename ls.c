// LS IMPLEMENTED
#include "headers.h"

int all(const struct dirent *d)
{
    return 1;
}

int alphasort_no_case(const struct dirent **first, const struct dirent **second)
{
    return strcasecmp((*first)->d_name, (*second)->d_name);
}

void print_long(char *dir_arg, struct dirent *dir_entry, int flag_a)
{
    struct stat statbuf;
    char fp[300];
    sprintf(fp, "%s/%s", dir_arg, dir_entry->d_name);
    if (stat(fp, &statbuf) == -1)
    {
        perror("stat");
        return;
    }

    // permission data/nlink
    printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
    printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
    printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
    printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
    printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
    printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf((statbuf.st_mode & S_IXOTH) ? "x " : "- ");
    printf("%li ", statbuf.st_nlink);

    // group and user data
    struct passwd *pw;
    struct group *gid;
    pw = getpwuid(statbuf.st_uid);
    if (pw == NULL)
    {
        perror("getpwuid");
        printf("%d ", statbuf.st_uid);
    }
    else
    {
        printf("%s ", pw->pw_name);
    }
    gid = getgrgid(statbuf.st_gid);
    if (gid == NULL)
    {
        perror("getpwuid");
        printf("%d ", statbuf.st_gid);
    }
    else
    {
        printf("%s ", gid->gr_name);
    }

    // file size
    printf("%5ld ", statbuf.st_size);

    // timestamp
    struct tm *tmp;
    char outstr[200];
    time_t t = statbuf.st_mtime;
    tmp = localtime(&t);
    if (tmp == NULL)
    {
        perror("localtime");
        exit(EXIT_FAILURE);
    }
    strftime(outstr, sizeof(outstr), "%b %d %R", tmp);
    printf("%s ", outstr);

    // file name
    // print color for directories
    if (stat(dir_entry->d_name, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
    {
        printf("\033[1;34m%s\033[0m\n", dir_entry->d_name);
    }
    // print color for executables
    else if (stat(dir_entry->d_name, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
    {
        printf("\033[1;32m%s\033[0m\n", dir_entry->d_name);
    }
    // print color for files
    else
    {
        printf("%s\n", dir_entry->d_name);
    }
}

void list_display(char *path, int flag_a, int flag_l, int flag_al)
{
    struct stat stat_list;
    stat(path, &stat_list);

    struct dirent **namelist;
    if (S_ISDIR(stat_list.st_mode))
    {
        // struct dirent ** directory_entry;
        if (flag_al == 1)
        {
            DIR *dir = opendir(path);
            if (dir == NULL)
            {
                printf("Cannot open directory\n");
                return;
            }

            int file_num = scandir(path, &namelist, all, alphasort_no_case);

            if (file_num > 0)
            {
                for (int i = 0; i < file_num; i++)
                {
                    print_long(path, namelist[i], flag_a);
                }
            }
            closedir(dir);
        }
        else if (flag_l == 1)
        {
            DIR *dir = opendir(path);
            if (dir == NULL)
            {
                printf("Cannot open directory\n");
                return;
            }

            int file_num = scandir(path, &namelist, all, alphasort_no_case);

            if (file_num > 0)
            {
                for (int i = 0; i < file_num; i++)
                {
                    if (strcmp(namelist[i]->d_name, ".") == 0 || strcmp(namelist[i]->d_name, "..") == 0)
                    {
                        continue;
                    }
                    print_long(path, namelist[i], flag_a);
                }
            }
            closedir(dir);
        }
        else if (flag_a == 1)
        {
            DIR *dir = opendir(path);

            // Ensure we can open directory.
            if (dir == NULL)
            {
                printf("Cannot open directory\n");
                return;
            }

            int file_num = scandir(path, &namelist, all, alphasort_no_case);
            // Process each entry.
            if (file_num > 0)
            {
                for (int i = 0; i < file_num; i++)
                {
                    // printf("\033[1;32m%s\033[0m\n", namelist[i]->d_name);
                    struct stat statbuf;
                    // print color for directories
                    if (stat(namelist[i]->d_name, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
                    {
                        printf("\033[1;34m%s\033[0m\n", namelist[i]->d_name);
                    }
                    // print color for executables
                    else if (stat(namelist[i]->d_name, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
                    {
                        printf("\033[1;32m%s\033[0m\n", namelist[i]->d_name);
                    }
                    // print color for files
                    else
                    {
                        printf("%s\n", namelist[i]->d_name);
                    }
                }
            }
            closedir(dir);
        }
    }
    else if (S_ISREG(stat_list.st_mode))
    { // If the path is a file
        if (flag_al == 1 || flag_l == 1)
        {

            // print_long(path, path, flag_a); // Pass flag_a to see if . and .. are to be printed
            struct stat statbuf;
            char cwd[200];
            getcwd(cwd, sizeof(cwd));
            char fp[300];
            sprintf(fp, "%s/%s", cwd, path);
            if (stat(fp, &statbuf) == -1)
            {
                perror("stat");
                return;
            }

            // permission data/nlink
            printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
            printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
            printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
            printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
            printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
            printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
            printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
            printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
            printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
            printf((statbuf.st_mode & S_IXOTH) ? "x " : "- ");
            printf("%li ", statbuf.st_nlink);

            // group and user data
            struct passwd *pw;
            struct group *gid;
            pw = getpwuid(statbuf.st_uid);
            if (pw == NULL)
            {
                perror("getpwuid");
                printf("%d ", statbuf.st_uid);
            }
            else
            {
                printf("%s ", pw->pw_name);
            }
            gid = getgrgid(statbuf.st_gid);
            if (gid == NULL)
            {
                perror("getpwuid");
                printf("%d ", statbuf.st_gid);
            }
            else
            {
                printf("%s ", gid->gr_name);
            }

            // file size
            printf("%5ld ", statbuf.st_size);

            // timestamp
            struct tm *tmp;
            char outstr[200];
            time_t t = statbuf.st_mtime;
            tmp = localtime(&t);
            if (tmp == NULL)
            {
                perror("localtime");
                exit(EXIT_FAILURE);
            }
            strftime(outstr, sizeof(outstr), "%b %d %R", tmp);
            printf("%s ", outstr);

            printf("%s\n", path);
        }
        else
        {
            printf("%s\n", path); // print the file name as it is
        }
    }
    else
    { // If the path is an executable file
        if (flag_al == 1 || flag_l == 1)
        {

            // print_long(path, namelist, flag_a); // Pass flag_a to see if . and .. are to be printed
            struct stat statbuf;
            char cwd[200];
            getcwd(cwd, sizeof(cwd));
            char fp[300];
            sprintf(fp, "%s/%s", cwd, path);
            if (stat(fp, &statbuf) == -1)
            {
                perror("stat");
                return;
            }

            // permission data/nlink
            printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
            printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
            printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
            printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
            printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
            printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
            printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
            printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
            printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
            printf((statbuf.st_mode & S_IXOTH) ? "x " : "- ");
            printf("%li ", statbuf.st_nlink);

            // group and user data
            struct passwd *pw;
            struct group *gid;
            pw = getpwuid(statbuf.st_uid);
            if (pw == NULL)
            {
                perror("getpwuid");
                printf("%d ", statbuf.st_uid);
            }
            else
            {
                printf("%s ", pw->pw_name);
            }
            gid = getgrgid(statbuf.st_gid);
            if (gid == NULL)
            {
                perror("getpwuid");
                printf("%d ", statbuf.st_gid);
            }
            else
            {
                printf("%s ", gid->gr_name);
            }

            // file size
            printf("%5ld ", statbuf.st_size);

            // timestamp
            struct tm *tmp;
            char outstr[200];
            time_t t = statbuf.st_mtime;
            tmp = localtime(&t);
            if (tmp == NULL)
            {
                perror("localtime");
                exit(EXIT_FAILURE);
            }
            strftime(outstr, sizeof(outstr), "%b %d %R", tmp);
            printf("%s ", outstr);

            printf("\033[1;32m%s\033[0m\n", path);
        }
        else
        {
            printf("\033[1;32m%s\033[0m\n", path); // print the file name as it is
        }
    }
}

void exec_ls(char *arg)
{
    int flag_zeroarg = 0,len=0;
    if (arg == NULL || strcmp(arg, "\n") == 0)
    {
        len=0;
        flag_zeroarg = 1;
    }
    else{
        len=strlen(arg);
    }
    int flag_a = 0, flag_l = 0, flag_al = 0;
    for (int i = 0; i < len; i++)
    {
        if (arg[i == '-'])
        {
            if (arg[i + 1] == 'a')
            {
                if (arg[i + 2] == 'l')
                {
                    flag_al = 1;
                }
                else
                {
                    flag_a = 1;
                }
            }
            else if (arg[i + 1] == 'l')
            {
                if (arg[i + 2] == 'a')
                {
                    flag_al = 1;
                }
                else
                {
                    flag_l = 1;
                }
            }
        }
    }

    if (flag_zeroarg == 1)
    {
        // char cwd[200];
        // getcwd(cwd, 200);
        // list_display(cwd, flag_a, flag_l, flag_al);
        struct dirent **entity;
        DIR *dir = opendir(".");

        // Ensure we can open directory.
        if (dir == NULL)
        {
            printf("Cannot open directory\n");
            return;
        }

        int file_num = scandir(".", &entity, all, alphasort_no_case);
        // Process each entry.
        if (file_num > 0)
        {
            for (int i = 0; i < file_num; i++)
            {
                if (strcmp(entity[i]->d_name, ".") == 0 || strcmp(entity[i]->d_name, "..") == 0)
                {
                    continue;
                }

                struct stat statbuf;
                // print color for directories
                if (stat(entity[i]->d_name, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
                {
                    printf("\033[1;34m%s\033[0m\n", entity[i]->d_name);
                }
                // print color for executables
                else if (stat(entity[i]->d_name, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
                {
                    printf("\033[1;32m%s\033[0m\n", entity[i]->d_name);
                }
                // print color for files
                else
                {
                    printf("%s\n", entity[i]->d_name);
                }
            }
        }

        closedir(dir);
    }
    else
    {
        int count = 0;
        char *tok = strtok(arg, " ");
        while (tok != NULL)
        {
            if (strcmp(tok, "-a") == 0 || strcmp(tok, "-l") == 0 || strcmp(tok, "-al") == 0 || strcmp(tok, "-la") == 0)
            {
                tok = strtok(NULL, " ");
                continue;
            }
            else
            {
                count++;
                list_display(tok, flag_a, flag_l, flag_al);
                tok = strtok(NULL, " ");
            }
        }
        if (count == 0) // if its only ls -a or ls -l or ls -al or ls -la
        {
            char cwd[200];
            getcwd(cwd, 200);
            list_display(cwd, flag_a, flag_l, flag_al);
        }
    }
}

