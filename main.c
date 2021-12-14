#include "headers.h"

int main()
{

    shell_pid = getpid();
    // getting user and system info
    username = getenv("USER");
    gethostname(systemname, 1000);
    getcwd(present_directory, sizeof(present_directory));
    strcpy(original_pwd, present_directory);
    chdir(present_directory);
    strcpy(previous_directory, present_directory);
    print_prompt();

    char semicolon[2] = ";";
    num_back_process = 0;
    signal(SIGCHLD, finished_background_process); // for the background functions when closing
    signal(SIGTSTP, ctrl_z);
    signal(SIGINT, ctrl_c);
    fore_process.pid = -1;

    ssize_t num_size = 0;
    while (1)
    {
        char *token_array[150];
        char *command_line;
        ll len;
        len = getline(&command_line, &num_size, stdin);
        if (len <= 0)
        {
            printf("\n");
            fflush(stdout);
            exit(0);
        }
        ll num_of_commands = 0; // no of commands in a line
        if (strcmp(command_line, "\n") == 0)
        {
            print_prompt();
            continue;
        }

        //tokenize based on semicolon
        token_array[num_of_commands] = strtok(command_line, semicolon);
        while (token_array[num_of_commands] != NULL)
        {
            num_of_commands = num_of_commands + 1;
            token_array[num_of_commands] = strtok(NULL, semicolon);
        }

        for (ll i = 0; i < num_of_commands; i++)
        {
            char *command;

            ll delim = 0;

            char orig_comm[2000];
            strcpy(orig_comm, token_array[i]);

            ll piping = 0;
            piping = pipe_check(orig_comm);
            if (piping)
            {
                pipe_func(orig_comm);
                continue;
            }

            delim = redirection_check(orig_comm);
            if (delim > 0)
            {
                redirection(orig_comm, delim);
                continue;
            }

            command = strtok(token_array[i], " \n\t\r");
            if (command == NULL)
            {
                continue;
            }

            if (strcmp(command, "exit") == 0)
            {
                exit(0);
            }
            else if (strcmp(command, "pwd") == 0)
            {
                pwd();
            }

            else
            {
                char command_strings[200][200];
                ll no_of_args = 0;
                while (command != NULL) // tokenize based on spaces
                {
                    strcpy(command_strings[no_of_args++], command);
                    command = strtok(NULL, " \n\t\r");
                }
                if (strcmp(command_strings[no_of_args - 1], "&") == 0)
                {
                    background_process(no_of_args, command_strings);
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
                else if (strcmp(command_strings[0], "replay") == 0)
                {
                    replay(no_of_args, command_strings, orig_comm);
                }

                else
                {
                    //printf("command no there\n");
                    foreground_process(no_of_args, command_strings);
                }
            }
        }
        print_prompt();
        //free(command_line);
    }
}