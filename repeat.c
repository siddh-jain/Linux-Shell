#include "headers.h"

void repeat(ll no_of_arg, char arg[][200])
{
    if (no_of_arg < 3)
    {
        printf("Minimum number of required arguments in repeat is 3\n");
        return;
    }
    ll new_no_of_arg;
    new_no_of_arg = no_of_arg - 2;

    char new_arg[200][200];
    for (ll i = 0; i < new_no_of_arg; i++)
    {
        strcpy(new_arg[i], arg[i + 2]);
    }
    ll no_of_times;
    no_of_times = arg[1][0] - 48;
    for (ll i = 0; i < no_of_times; i++) // repeat the funftions no_of_times
    {
        if (strcmp(new_arg[0], "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(new_arg[0], "pwd") == 0)
        {
            pwd();
        }
        else if (strcmp(new_arg[0], "repeat") == 0)
        {
            repeat(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "echo") == 0)
        {
            echo(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "cd") == 0)
        {
            cd(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "ls") == 0)
        {
            ls(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "pinfo") == 0)
        {
            pinfo(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "jobs") == 0)
        {
            jobs(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "sig") == 0)
        {
            sig(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "fg") == 0)
        {
            fg(new_no_of_arg, new_arg);
        }
        else if (strcmp(new_arg[0], "bg") == 0)
        {
            bg(new_no_of_arg, new_arg);
        }

        else
        {
            foreground_process(new_no_of_arg, new_arg);
        }
    }
}
