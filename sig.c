#include "headers.h"

void sig(ll no_of_arg, char arg[][200])
{
    ll job_number, signal_number;
    job_number = atoi(arg[1]);
    signal_number = atoi(arg[2]);

    if (no_of_arg != 3)
    {
        printf("Error: Incorrect number of arguments");
        return;
    }
    ll back_process_num=-1;
    ll i;
    for (i = 1; i <= num_back_process; i++)
    {
        if (job_number == back_process[i].process_num)
        {
            back_process_num = i;
            break;
        }
    }

    if (job_number > 0 && job_number <= num_back_process && back_process_num>0)
    {
        kill(back_process[back_process_num].pid, signal_number);
    }
    else
    {
        printf("Error: No such process exist\n");
    }
}
