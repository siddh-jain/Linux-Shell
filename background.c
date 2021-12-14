#include "headers.h"

void background_process(ll no_of_arg, char arg[][200])
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
        exit(EXIT_SUCCESS);
    }
    else //parent process
    {
        num_back_process++;
        back_process[num_back_process].pid = pid;
        strcpy(back_process[num_back_process].name, arg[0]);

        ll number_to_put = 1;
        for (ll i = 1; i < num_back_process; i++)
        {
            if (back_process[i].process_num >= number_to_put)
            {
                number_to_put = back_process[i].process_num + 1;
            }
        }
        back_process[num_back_process].process_num = number_to_put;

        printf("[%lld] %d\n", number_to_put, pid);
    }
}

void finished_background_process()
{
    int status;
    pid_t pid;
    pid = waitpid(WAIT_ANY, &status, WNOHANG); // get pid of process
    for (ll i = 1; i <= num_back_process; i++) // check for process in background_process array
    {
        // if (pid < 0)
        // {
        //     perror("ERR-waitpid:");
        // }
        int exit_status = WEXITSTATUS(status);
        if (back_process[i].pid == pid)
        {
            if (!exit_status)
            {
                fprintf(stderr, "\n%s with pid %d exited normally with exit status: %d\n", back_process[i].name, pid, exit_status);
            }
            else
            {
                fprintf(stderr, "\n%s with pid %d exited abnormally with exit status: %d\n", back_process[i].name, pid, exit_status);
            }
            back_process[i].process_num = -1;
            print_prompt();
            fflush(stdout);
            break;
        }
    }
    signal(SIGCHLD, finished_background_process);
}
