#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

typedef long long int ll;

typedef struct process
{
    char name[200];
    ll pid;
    ll process_num;
} process;

char *username;
char systemname[1000];
char present_directory[1000];
char curr_dir[1000];
char original_pwd[1000];
ll num_back_process;
process back_process[2020];
char previous_directory[1000];
char history[20][200];
process fore_process;
ll shell_pid;

void print_prompt();
void echo(ll no_of_arg, char arg[][200]);
void pwd();
void cd(ll no_of_arg, char arg[][200]);
void ls(ll no_of_arg, char arg[][200]);
void list(char *arg, ll count, ll flag_a, ll flag_l);
char *get_permissions(struct stat s);
void foreground_process(ll no_of_arg, char arg[][200]);
void background_process(ll no_of_arg, char arg[][200]);
void pinfo(ll no_of_arg, char arg[][200]);
void repeat(ll no_of_arg, char arg[][200]);
void finished_background_process();
int get_block_size(char *present_dir,ll flag_a);

// part 2:

ll redirection_check(char *orig_comm);
void redirection(char orig_comm[],ll delim_flag);
void run_command(char command_strings[][200], ll no_of_args,int old_output,int fdo,int fdi);
ll pipe_check(char *command);
void pipe_func(char orig_command[]);
void jobs(ll no_of_arg, char arg[][200]);
int comparator(const void *c0,const void *c1);
void sig(ll no_of_arg, char arg[][200]);
void fg(ll no_of_arg, char arg[][200]);
void bg(ll no_of_arg, char arg[][200]);
void ctrl_z(int signo);
void ctrl_c(int signo);
void replay(ll no_of_arg, char arg[][200],char orig_comm[]);

#endif