#include "headers.h"

void jobs(ll no_of_arg, char arg[][200])
{
    ll flag_r = 1, flag_s = 1;

    for (ll i = 0; i < no_of_arg; i++)
    {
        if (strcmp(arg[i], "-r") == 0)
        {
            flag_s = 0;
            flag_r = 1;
        }
        if (strcmp(arg[i], "-s") == 0)
        {
            flag_r = 0;
            flag_s = 1;
        }
        if (strcmp(arg[i], "-rs") == 0 || strcmp(arg[i], "-rs") == 0)
        {
            flag_s = 1;
            flag_r = 1;
        }
    }

    qsort(&back_process[1],num_back_process,sizeof(process),comparator);

    for (ll i = 1; i <= num_back_process; i++)
    {
        char path[2000], pid_str[15], status;
        sprintf(pid_str, "%lld", back_process[i].pid);
        sprintf(path, "/proc/%s/stat", pid_str);

        if(back_process[i].process_num<0)
        {
            continue;
        }
        FILE *fd;
        if ((fd = fopen(path, "r")) == NULL)
        {
            //printf("[%lld] Done %s [%lld]\n", back_process[i].process_num, back_process[i].name, back_process[i].pid);
        }
        else
        {
            int p;
            long unsigned mem;
            fscanf(fd, "%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &p, &status, &mem);
            fclose(fd);

            if(status== 'T' && flag_s==1)
            {
                printf("[%lld] Stopped %s [%lld]\n", back_process[i].process_num, back_process[i].name, back_process[i].pid);
            }
            else if(flag_r==1)
            {
                printf("[%lld] Running %s [%lld]\n", back_process[i].process_num, back_process[i].name, back_process[i].pid);
            }
        }
    }
}

int comparator(const void *c0,const void *c1)
{
    process p0 = *(process*)c0;
    process p1 = *(process*)c1;
    return(strcmp(p0.name,p1.name));
}

