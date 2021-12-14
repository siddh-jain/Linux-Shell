#include "headers.h"

void replay(ll no_of_arg, char arg[][200], char orig_comm[])
{
    ll new_no_of_arg = 0;
    char new_arg[200][200];
    ll interval = -1;
    ll period = -1;
    ll flag = 0;

    for (ll i = 1; i < no_of_arg; i++)
    {
        if (strcmp(arg[i], "-command") == 0)
        {
            flag = 1;
            i++;
            while ((strcmp(arg[i], "-interval") != 0 && strcmp(arg[i], "-period") != 0) && i < no_of_arg)
            {
                strcpy(new_arg[new_no_of_arg], arg[i]);
                new_no_of_arg++;

                //printf("com:%s\n", arg[i]);
                i++;
            }
        }
        if (strcmp(arg[i], "-interval") == 0)
        {
            if (i + 2 < no_of_arg && (strcmp(arg[i + 2], "-period") != 0 && strcmp(arg[i + 2], "-command") != 0))
            {
                printf("Incorrect arguments in replay\n");
                return;
            }
            i++;
            interval = atoi(arg[i]);
            //printf("int:%s\n", arg[i]);
        }

        if (strcmp(arg[i], "-period") == 0)
        {

            if (i + 2 < no_of_arg && (strcmp(arg[i + 2], "-interval") != 0 && strcmp(arg[i + 2], "-command") != 0))
            {
                printf("Incorrect arguments in replay\n");
                return;
            }
            i++;
            period = atoi(arg[i]);
            //printf("per:%s\n", arg[i]);
        }
    }

    if (interval < 1 || period < 1 || flag == 0)
    {
        printf("Incorrect arguments in replay\n");
        return;
    }

    ll no_of_times;
    no_of_times = period / interval;

    ll remaining_time;
    remaining_time = period - no_of_times * interval;

    //printf("%lld %lld %lld\n", interval, period, new_no_of_arg);

    for (ll i = 0; i < no_of_times; i++) // repeat the funftions no_of_times
    {
        sleep(interval);
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
    sleep(remaining_time);
}