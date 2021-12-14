#include "headers.h"

void bg(ll no_of_arg, char arg[][200])
{
    if (no_of_arg != 2)
    {
        printf("Incorrect number of arguments\n");
        return;
    }
    ll process_no = atoi(arg[1]);

    if (process_no < 1 || process_no > num_back_process)
    {
        printf("Err:No such process exists\n");
        return;
    }

    ll back_process_num = -1;
    for (ll i = 0; i <= num_back_process; i++)
    {
        if (process_no == back_process[i].process_num)
        {
            back_process_num = i;
            break;
        }
    }

    if (back_process_num < 0)
    {
        printf("Err:No such process exists\n");
        return;
    }

    char path[2000], pid_str[15];
    sprintf(pid_str, "%lld", back_process[back_process_num].pid);
    sprintf(path, "/proc/%s/stat", pid_str);

    FILE *fd;
    if ((fd = fopen(path, "r")) == NULL)
    {
        printf("Process has exited: Cannot change its state\n");
        return;
    }
    else
    {
        kill(back_process[back_process_num].pid, SIGTTIN);
        kill(back_process[back_process_num].pid, SIGCONT);
    }
}