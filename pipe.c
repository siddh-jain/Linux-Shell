#include "headers.h"

ll pipe_check(char *command)
{
    ll pipe_flag = 0;
    ll len;
    len = strlen(command);
    for (ll i = 0; i < len; i++)
    {
        if (command[i] == '|')
        {
            pipe_flag = 1;
            break;
        }
    }
    return pipe_flag;
}

void pipe_func(char orig_command[])
{
    char *parts[2000];

    ll no_of_commands = 0;
    parts[no_of_commands] = strtok(orig_command, "|");
    while (parts[no_of_commands] != NULL)
    {
        no_of_commands = no_of_commands + 1;
        parts[no_of_commands] = strtok(NULL, "|");
    }

    char part_orig_comm[2000], tempo[2000];
    int odd_pipe[2], even_pipe[2], odd = 1, even = 0, inp = 0, out = 1;

    for (ll part_num = 0; part_num < no_of_commands; part_num++)
    {

        strcpy(part_orig_comm, parts[part_num]);
        strcpy(tempo, parts[part_num]);

        char *command;
        char command_strings[200][200];
        ll no_of_args = 0;
        command = strtok(part_orig_comm, " \n\t\r");
        while (command != NULL) // tokenize based on spaces
        {
            strcpy(command_strings[no_of_args++], command);
            command = strtok(NULL, " \n\t\r");
        }

        if ((part_num % 2) == 0)
        {
            int k;
            k = pipe(even_pipe);
            if (k < 0)
            {
                printf("Error in creating pipe\n");
            }
        }
        else
        {
            int k;
            k = pipe(odd_pipe);
            if (k < 0)
            {
                printf("Error in creating pipe\n");
            }
        }

        int pid = fork();
        if (pid < 0)
        {
            printf("Error:failed to fork\n");
            return;
        }
        else if (pid == 0)
        {

            if (part_num == 0)
            {
                dup2(even_pipe[1], 1); //output to even_piep
                close(even_pipe[0]);   // closing the input of even_pipe
            }

            else if (part_num == no_of_commands - 1)
            {
                if ((part_num % 2) == even)
                {
                    dup2(odd_pipe[0], 0);
                }
                else
                {
                    dup2(even_pipe[0], 0);
                }
            }

            else if ((part_num % 2) == even)
            {
                dup2(odd_pipe[0], 0);  // innput from odd_pipe
                dup2(even_pipe[1], 1); // output to even_pipe
                close(even_pipe[0]);
            }
            else if ((part_num % 2) == odd)
            {
                dup2(even_pipe[0], 0);
                dup2(odd_pipe[1], 1);
                close(even_pipe[1]);
            }

            ll redir = 0;
            redir = redirection_check(tempo);
            if (redir > 0)
            {
                redirection(tempo, redir);
                //printf("here");
            }
            else
            {
                if (strcmp(command_strings[0], "pwd") == 0)
                {
                    pwd();
                }
                else if (strcmp(command_strings[0], "repeat") == 0)
                {
                    repeat(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "echo") == 0)
                {
                    echo(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "cd") == 0)
                {
                    cd(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "ls") == 0)
                {
                    ls(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "pinfo") == 0)
                {
                    pinfo(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "jobs") == 0)
                {
                    jobs(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "sig") == 0)
                {
                    sig(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "fg") == 0)
                {
                    fg(no_of_args, command_strings);
                }
                else if (strcmp(command_strings[0], "bg") == 0)
                {
                    bg(no_of_args, command_strings);
                }

                else
                {

                    char *commands[no_of_args + 1];
                    ll c;
                    for (c = 0; c < no_of_args;)
                    {
                        commands[c] = command_strings[c];
                        c++;
                    }
                    commands[no_of_args] = NULL;

                    if (execvp(commands[0], commands) < 0)
                    {
                        printf("%s: command not found\n", command_strings[0]);
                    }
                }
            }
            exit(0);
        }
        else
        {
            wait(NULL);

            if (part_num == 0)
            {
                close(even_pipe[1]);
            }

            else if (part_num == no_of_commands - 1)
            {
                if ((part_num % 2) == even)
                {
                    close(odd_pipe[0]);
                }
                else
                {
                    close(even_pipe[0]);
                }
            }

            else if ((part_num % 2) == even)
            {
                close(odd_pipe[0]);
                close(even_pipe[1]);
            }
            else if ((part_num % 2) == odd)
            {
                close(odd_pipe[1]);
                close(even_pipe[0]);
            }
        }
    }
}