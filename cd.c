#include "headers.h"

void cd(ll no_of_arg, char arg[][200])
{
    if (no_of_arg >= 3)
    {
        printf("cd: too many arguments\n");
    }

    if (no_of_arg < 2) // change to home directory
    {
        char *cwd = (char *)malloc(1000 * sizeof(char));
        cwd = getcwd(cwd, 1000);
        strcpy(previous_directory, cwd);
        chdir(present_directory);
        free(cwd);
    }
    else
    {
        char pathname[5000], given_pathname[5000];
        strcpy(pathname, arg[1]);
        strcpy(given_pathname, arg[1]);
        if (strcmp(pathname, "~") == 0) // change to home directory
        {
            char *cwd = (char *)malloc(1000 * sizeof(char));
            cwd = getcwd(cwd, 1000);
            strcpy(previous_directory, cwd);
            chdir(present_directory);
            free(cwd);
            return;
        }
        if (strcmp(pathname, "-") == 0) // change to previous directory
        {
            char *cwd = (char *)malloc(1000 * sizeof(char));
            cwd = getcwd(cwd, 1000);
            char temp[1000];
            strcpy(temp, previous_directory);
            strcpy(previous_directory, cwd);
            chdir(temp);
            free(cwd);
            return;
        }
        else if (pathname[0] == '~') /// for path given from pseudo home directory
        {
            if (strlen(pathname) > 1)
            {
                char temp[1000];
                strcpy(temp, original_pwd);
                strcat(temp, &pathname[1]);
                strcpy(pathname, temp);
            }
        }
        char *cwd = (char *)malloc(1000 * sizeof(char)); // store current working directory for previous directory.
        cwd = getcwd(cwd, 1000);
        char temp[1000];
        strcpy(temp, cwd);
        free(cwd);

        ll check_file = chdir(pathname); //check if file is present
        if (check_file >= 0)
        {
            strcpy(previous_directory, temp);
        }
        else
        {
            printf("cd: %s: No such file or directory\n", given_pathname);
        }
        return;
    }
}