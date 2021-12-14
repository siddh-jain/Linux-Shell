#include "headers.h"

void pinfo(ll no_of_arg, char arg[][200])
{
    int pid;
    char id[50];
    char path[2000];
    char filepath[2000];
    if (no_of_arg > 1) //for other processes
    {
        sprintf(path, "/proc/%s/stat", arg[1]);
        sprintf(filepath, "/proc/%s/exe", arg[1]);
        strcpy(id, arg[1]);
    }
    else // for shell
    {

        sprintf(id, "%d", getpid());
        sprintf(path, "/proc/%s/stat", id);
        sprintf(filepath, "/proc/%s/exe", id);
    }
    //strcpy(filepath, path);
    FILE *stat_file;
    stat_file = fopen(path, "r");
    if (stat_file == NULL)
    {
        printf("ERROR: The process does not exist\n");
        return;
    }
    else
    {
        if (no_of_arg > 1)
        {
            printf("pid -- %s\n", arg[1]);
        }
        else
        {
            printf("pid -- %s\n", id);
        }

        // get the status , memory size and id's if its runnning in fore/back-ground
        char buff[2000], status[5], memory[100], ppid[1000], pgrp[1000];
        ll i = 1;
        for (i = 1; fscanf(stat_file, "%s", buff) == 1; i++)
        {
            if (i == 3)
            {
                strcpy(status, buff);
            }
            if (i == 23)
            {
                strcpy(memory, buff);
            }
            if (i == 5)
            {
                strcpy(ppid, buff);
            }
            if (i == 8)
            {
                strcpy(pgrp, buff);
            }
        }
        fclose(stat_file);
        printf("Process Status -- %s", status);
        if ((strcmp(ppid, pgrp) == 0) && (strcmp(status, "S") == 0 || strcmp(status, "R") == 0))
        {
            printf("+\n");
        }
        else
        {
            printf("\n");
        }
        printf("memory -- %s {Virtual Memory}\n", memory);

        //finding and printing executable path
        char exec_path[2000];
        int len;
        len = readlink(filepath, exec_path, 2000);
        if (len == -1)
        {
            printf("Cannot find executable path for pid: %s\n", id);
            return;
        }
        exec_path[len] = '\0';

        char *pointer = strstr(exec_path, original_pwd);
        if (pointer != NULL)
        {
            char temp[2000];
            sprintf(temp, "%s%s", "~", pointer + strlen(original_pwd));
            strcpy(exec_path, temp);
        }
        printf("Executable Path -- %s\n", exec_path);
    }
}