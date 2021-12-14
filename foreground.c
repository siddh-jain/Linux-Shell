#include "headers.h"

void foreground_process(ll no_of_arg, char arg[][200])
{
    int pid;
    pid = fork();
    // converting arg into char* a[] form
    char *commands[no_of_arg + 1];
    ll c;
    for (c = 0; c < no_of_arg;)
    {
        commands[c] = arg[c];
        c++;
    }
    commands[no_of_arg] = NULL;

    // if fork didnt properly
    if (pid < 0)
    {
        perror("ERROR:");
        printf("\n");
        return;
    }
    else if (pid == 0) //for child process
    {
        if (execvp(commands[0], commands) < 0)
        {
            printf("%s: command not found\n", arg[0]);
            exit(EXIT_FAILURE);
        }
    }
    else //parent process
    {
        int status;
        strcpy(fore_process.name,arg[0]);
        fore_process.pid=pid;
        waitpid(pid, &status, WUNTRACED);
        fore_process.pid=-1;
    }
}