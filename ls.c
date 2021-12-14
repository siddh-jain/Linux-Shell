#include "headers.h"

void ls(ll no_of_arg, char arg[][200])
{
    // initialising flags.
    ll flag_a = 0;
    ll flag_l = 0;
    char flag1[3] = "-l";
    char flag2[3] = "-a";
    char flag3[4] = "-al";
    char flag4[4] = "-la";

    for (ll i = 0; i < no_of_arg; i++) // checking for flags.
    {
        if (arg[i][0] == '-')
        {
            char tem[500];
            strcpy(tem, arg[i]);
            char *p;
            if ((p = strchr(tem, 'l')) != NULL)
            {
                flag_l = 1;
            }
            if ((p = strchr(tem, 'a')) != NULL)
            {
                flag_a = 1;
            }
        }
    }

    ll count = 0;
    for (ll i = 1; i < no_of_arg; i++) // checking  number of non flag elements.
    {
        if ((strcmp(arg[i], flag1) != 0) && (strcmp(arg[i], flag2) != 0) && (strcmp(arg[i], flag3) != 0) && (strcmp(arg[i], flag4) != 0))
        {
            if (arg[i][0] != '-')
            {
                count = count + 1;
            }
            else
            {
                printf("ls: invalid option: %s\n", arg[i]);
                return;
            }
        }
    }

    ll list_one_by_one = 1;
    for (ll i = 1; i < no_of_arg; i++) // call list according to flags
    {
        if ((arg[i][0] != '-') && (strcmp(arg[i], flag1) != 0) && (strcmp(arg[i], flag2) != 0) && (strcmp(arg[i], flag3) != 0) && (strcmp(arg[i], flag4) != 0))
        {
            list(arg[i], count, flag_a, flag_l);
            list_one_by_one = 0;
            //printf("list one by one\n");
        }
    }
    if (list_one_by_one)
    {
        //printf("list all,%lld\n",count);
        list(NULL, 0, flag_a, flag_l);
    }
}

void list(char *arg, ll count, ll flag_a, ll flag_l)
{
    // appending directory
    char dir_name[2000];
    if (arg == NULL)
    {
        strcpy(dir_name, "./");
    }
    else
    {
        ll path_len = strlen(arg);
        if (arg[0] != '~')
        {
            strcpy(dir_name, arg);
        }
        else if (strcmp(arg, "~") == 0)
        {
            strcpy(dir_name, original_pwd);
        }
    }

    struct stat d;
    mode_t mode;

    if (stat(dir_name, &d) != 0)
    {
        printf("ls: cannot access '%s': No such file or directory\n", dir_name);
        return;
    }

    mode = d.st_mode;
    if (S_ISDIR(mode))
    {

        strcat(dir_name, "/");
        DIR *dir;

        struct dirent *entry;
        dir = opendir(dir_name);
        if (dir == NULL)
        {
            perror("Directory Opening: ");
            return;
        }
        entry = readdir(dir);
        if (entry == NULL)
        {
            perror("ERROR in seeing entries of Directory: ");
        }
        struct stat FILE;
        char FILE_path[2000];

        if (flag_l == 1)
        {
            ll total = get_block_size(dir_name, flag_a);
            printf("total %lld\n", total);
        }

        while (entry)
        {
            char *FILE_name;
            FILE_name = entry->d_name;
            strcpy(FILE_path, dir_name);
            strcat(FILE_path, FILE_name);

            if (stat(FILE_path, &FILE) != 0)
            {
                printf("ERROR in opening directory\n");
                entry = readdir(dir);
            }
            else
            {
                if ((flag_a == 0) && (FILE_name[0] == '.'))
                {
                    entry = readdir(dir);
                    continue;
                }

                if (flag_l == 0)
                {
                    printf("%s\n", FILE_name);
                }
                else
                {
                    char *permissions;
                    permissions = get_permissions(FILE);

                    nlink_t number;
                    number = FILE.st_nlink;

                    struct passwd *usr_name;
                    usr_name = getpwuid(FILE.st_uid);

                    struct group *grp_name;
                    grp_name = getgrgid(FILE.st_gid);

                    off_t size;
                    size = FILE.st_size;

                    char file_time[1000];
                    struct tm *temp_time;
                    temp_time = localtime(&FILE.st_mtime);
                    strftime(file_time, 1000, "%b %d %H:%M", temp_time);
                    char file_time1[1000];
                    strftime(file_time1, 1000, "%b %d  %Y", temp_time);

                    int year = temp_time->tm_year;
                    int month = temp_time->tm_mon;
                    int day = temp_time->tm_mday;

                    time_t my_time;
                    struct tm *timeinfo;
                    time(&my_time);
                    timeinfo = localtime(&my_time);

                    ll month_diff;
                    if ((timeinfo->tm_year - year) > 1)
                    {
                        printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time1, FILE_name);
                    }
                    else
                    {
                        month_diff = (timeinfo->tm_year - year) * 12 + timeinfo->tm_mon - month;
                        if (month_diff > 6)
                        {
                            printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time1, FILE_name);
                        }
                        else if (month_diff < 6)
                        {
                            printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time, FILE_name);
                        }
                        else
                        {
                            if (timeinfo->tm_mday >= day)
                            {
                                printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time1, FILE_name);
                            }
                            else
                            {
                                printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time, FILE_name);
                            }
                        }
                    }

                    //printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time, FILE_name);
                }

                entry = readdir(dir);
            }
        }
        closedir(dir);
    }
    else
    {
        struct stat FILE = d;
        char *FILE_name = dir_name;

        if (!(flag_a == 0 && FILE_name[0] == '.'))
        {
            if (!flag_l)
            {
                printf("%s\n", FILE_name);
            }
            else
            {
                char *permissions;
                permissions = get_permissions(FILE);

                nlink_t number;
                number = FILE.st_nlink;

                struct passwd *usr_name;
                usr_name = getpwuid(FILE.st_uid);

                struct group *grp_name;
                grp_name = getgrgid(FILE.st_gid);

                off_t size;
                size = FILE.st_size;

                char file_time[1000];
                struct tm *temp_time;
                temp_time = localtime(&FILE.st_mtime);
                strftime(file_time, 1000, "%b %d %H:%M", temp_time);
                char file_time1[1000];
                strftime(file_time1, 1000, "%b %d  %Y", temp_time);

                int year = temp_time->tm_year;
                int month = temp_time->tm_mon;
                int day = temp_time->tm_mday;

                time_t my_time;
                struct tm *timeinfo;
                time(&my_time);
                timeinfo = localtime(&my_time);

                ll month_diff;
                if ((timeinfo->tm_year - year) > 1)
                {
                    printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time1, FILE_name);
                }
                else
                {
                    month_diff = (timeinfo->tm_year - year) * 12 + timeinfo->tm_mon - month;
                    if (month_diff > 6)
                    {
                        printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time1, FILE_name);
                    }
                    else if (month_diff < 6)
                    {
                        printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time, FILE_name);
                    }
                    else
                    {
                        if (timeinfo->tm_mday >= day)
                        {
                            printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time1, FILE_name);
                        }
                        else
                        {
                            printf("%s %2ld %s %s %10ld %s %s\n", permissions, number, usr_name->pw_name, grp_name->gr_name, size, file_time, FILE_name);
                        }
                    }
                }
            }
        }
    }
}

char *get_permissions(struct stat s)
{
    char permission[11];
    mode_t mode = s.st_mode;

    permission[0] = (S_ISDIR(mode) ? 'd' : '-');
    permission[1] = ((mode & S_IRUSR) ? 'r' : '-');
    permission[2] = ((mode & S_IWUSR) ? 'w' : '-');
    permission[3] = ((mode & S_IXUSR) ? 'x' : '-');
    permission[4] = ((mode & S_IRGRP) ? 'r' : '-');
    permission[5] = ((mode & S_IWGRP) ? 'w' : '-');
    permission[6] = ((mode & S_IXGRP) ? 'x' : '-');
    permission[7] = ((mode & S_IROTH) ? 'r' : '-');
    permission[8] = ((mode & S_IWOTH) ? 'w' : '-');
    permission[9] = ((mode & S_IXOTH) ? 'x' : '-');
    permission[10] = '\0';

    char *temp = malloc(1024);
    strcpy(temp, permission);

    return temp;
}

int get_block_size(char *folder_dir, ll flag_a)
{
    int size;
    size = 0;
    DIR *d;
    struct stat fileStat;
    struct dirent *direc;
    int count;
    char folder = '.';
    d = opendir(folder_dir);
    if (d)
    {
        count = 0;
        while ((direc = readdir(d)) != NULL)
        {
            if (direc->d_name[0] == folder && flag_a == 0)
            {
                continue;
            }
            count++;
            char info_path[PATH_MAX + 1];
            strcpy(info_path, folder_dir);
            int flag = 0;
            if (folder_dir[strlen(folder_dir) - 1] != 47)
            {
                strcat(info_path, "/");
                flag = 1;
            }

            strcat(info_path, direc->d_name);

            stat(info_path, &fileStat);

            size = size + fileStat.st_blocks;
        }
    }
    else
    {
        printf("error acessing directory\n");
    }
    //printf("%d",count);

    return size / 2;
}