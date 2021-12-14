#include "headers.h"

void print_prompt()
{
    strcpy(curr_dir, "");

    char cwd[2000];
    getcwd(cwd, 2000);
    ll x = 0;
    if (strcmp(cwd, present_directory) != 0)
    {
        ll i = 0;
        while (present_directory[i])
        {
            if (present_directory[i] != cwd[i])
            {
                x = i;
                break;
            }
            i = i + 1;
        }

        if (x != 0) // files or folder other than home directory
        {
            strcpy(curr_dir, cwd);
        }
        else // files or folder in home directory
        {
            curr_dir[0] = '~';
            ll t, j = i;
            for (t = 1; cwd[j]; t++)
            {
                curr_dir[t] = cwd[j];
                j++;
            }
            curr_dir[t] = '\0';
        }
    }
    else //its home directory
    {
        strcpy(curr_dir, "~");
    }

    printf("<%s%s@%s%s:%s%s%s>", "\033[1;32m", username, systemname, "\033[0m", "\033[1;34m", curr_dir, "\033[0m");
}