#include "headers.h"

void ctrl_c(int signo)
{
    pid_t pid = getpid();

    if (pid != shell_pid)
        return;

    if (fore_process.pid == -1)
    {
        printf("\n");
        print_prompt();
        fflush(stdout);
    }

    if (fore_process.pid != -1)
    {
        kill(fore_process.pid, SIGINT);
    }
    signal(SIGINT, ctrl_c);
}

void ctrl_z(int signo)
{
    pid_t pid = getpid();

    if (pid != shell_pid)
        return;

    if (fore_process.pid == -1)
    {
        printf("\n");
        print_prompt();
        fflush(stdout);
    }

    if (fore_process.pid != -1)
    {
        kill(fore_process.pid, SIGTTIN);
        kill(fore_process.pid, SIGTSTP);
        num_back_process++;
        back_process[num_back_process].pid = fore_process.pid;
        strcpy(back_process[num_back_process].name, fore_process.name);

        ll number_to_put = 1;
        for (ll i = 1; i < num_back_process; i++)
        {
            if (back_process[i].process_num >= number_to_put)
            {
                number_to_put = back_process[i].process_num + 1;
            }
        }
        back_process[num_back_process].process_num = number_to_put;
    }
    signal(SIGTSTP, ctrl_z);
}