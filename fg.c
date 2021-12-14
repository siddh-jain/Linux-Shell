#include "headers.h"

void fg(ll no_of_arg, char arg[][200])
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
        printf("Err:No such process exists\n");
        return;
    }
    else
    {
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, back_process[back_process_num].pid);

        //adding to foreground process struct
        strcpy(fore_process.name, back_process[back_process_num].name);
        fore_process.pid = back_process[back_process_num].pid;

        // making process go to foreground
        kill(back_process[back_process_num].pid, SIGCONT);
        back_process[back_process_num].process_num = -1;
        waitpid(-1, NULL, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, getpgrp());
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        fore_process.pid = -1;
    }
}
