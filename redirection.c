#include "headers.h"

int status;

ll redirection_check(char *orig_comm)
{
    ll len = strlen(orig_comm);

    for (ll i = 0; i < len; i++)
    {
        if (orig_comm[i] == '>' && orig_comm[i + 1] == '>')
        {
            return 3;
        }
    }

    for (ll i = 0; i < len; i++)
    {
        if (orig_comm[i] == '>' || orig_comm[i] == '<')
        {
            return 2;
        }
    }

    return 0;
}

void redirection(char orig_comm[], ll delim_flag)
{
    int fdi = -1, fdo = -1;

    char inputfile[2000], outputfile[2000];
    strcpy(inputfile, "");
    strcpy(outputfile, "");

    char delim[5];
    if (delim_flag == 3)
    {
        strcpy(delim, ">>");
    }
    else
    {
        strcpy(delim, ">");
    }

    ll t = 0;
    char *temp[2000];
    temp[t] = strtok(orig_comm, delim);
    while (temp[t] != NULL)
    {
        t++;
        temp[t] = strtok(NULL, delim);
    }
    if (t == 2)
    {
        char *out[2];
        out[0] = strtok(temp[1], " \n\t\r");
        strcpy(outputfile, out[0]);
        //printf("file:%s.\n",outputfile);
    }

    //printf("\n\n.%s.\n.%s.\n\n",temp[0],temp[1]);

    char delim_input[5];
    strcpy(delim_input, "<");
    //return;
    ll u = 0;
    char *temp1[2000];
    temp1[0] = strtok(temp[0], delim_input);
    while (temp1[u] != NULL)
    {
        u++;
        temp1[u] = strtok(NULL, delim_input);
    }
    if (u == 2)
    {
        char *in[2];
        in[0] = strtok(temp1[1], " \n\t\r");
        strcpy(inputfile, in[0]);
        //printf("file:%s.\n",inputfile);
    }
    //return;

    char *command;
    char command_strings[200][200];
    ll no_of_args = 0;
    command = strtok(temp1[0], " \n\t\r");
    while (command != NULL) // tokenize based on spaces
    {
        strcpy(command_strings[no_of_args++], command);
        command = strtok(NULL, " \n\t\r");
    }

    if (strcmp("", inputfile) == 0 && strcmp("", outputfile) != 0) //output only
    {

        int old_output = dup(STDOUT_FILENO);
        int pid = fork();
        if (pid < 0)
        {
            printf("failed to fork\n");
            return;
        }

        if (strcmp(delim, ">>") == 0)
        {
            fdo = open(outputfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else if (strcmp(delim, ">") == 0)
        {
            fdo = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        dup2(fdo, 1);

        if (pid > 0)
        {
            while (wait(&status) != pid)
            {
                ;
            }
            dup2(old_output, 1);
            close(fdo);
        }
        else
        {
            run_command(command_strings, no_of_args, old_output, fdo, fdi);
            exit(0);
        }
    }
    else if (strcmp("", inputfile) != 0 && strcmp("", outputfile) == 0) //input only
    {
        int old_input = dup(STDIN_FILENO);
        int pid = fork();
        if (pid < 0)
        {
            printf("failed to fork\n");
            return;
        }

        fdi = open(inputfile, O_RDONLY);
        if (fdi < 0 && pid == 0)
        {
            printf("Input file dosent exist\n");
        }

        if (pid > 0)
        {
            while (wait(&status) != pid)
            {
                ;
            }
        }
        else
        {
            if (fdi >= 0)
            {
                dup2(fdi, 0);
                run_command(command_strings, no_of_args, -1, fdo, fdi);
                dup2(old_input, 0);
            }
            exit(0);
        }
    }
    else // both
    {
        int old_output = dup(STDOUT_FILENO);
        int old_input = dup(STDIN_FILENO);
        int pid = fork();
        if (pid < 0)
        {
            printf("failed to fork\n");
            return;
        }

        fdi = open(inputfile, O_RDONLY);
        if (fdi < 0 && pid == 0)
        {
            printf("Input file dosent exist\n");
        }
        if (strcmp(delim, ">>") == 0)
        {
            fdo = open(outputfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else if (strcmp(delim, ">") == 0)
        {
            fdo = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            //printf("here");
        }
        dup2(fdo, 1);

        if (pid > 0)
        {
            while (wait(&status) != pid)
            {
                ;
            }
            dup2(old_output, 1);
            close(fdi);
        }
        else
        {
            if (fdi >= 0)
            {
                dup2(fdi, 0);
                run_command(command_strings, no_of_args, old_output, fdo, fdi);
                dup2(old_input, 0);
            }
            exit(0);
        }
    }
}

void run_command(char command_strings[][200], ll no_of_args, int old_output, int fdo, int fdi)
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
            dup2(old_output, 1);
            printf("%s: command not found\n", command_strings[0]);

            if (fdo > -1)
            {
                close(fdo);
            }
            if (fdi > -1)
            {
                close(fdi);
            }
        }
    }
}