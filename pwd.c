#include "headers.h"

void pwd()
{
    char *pwd=(char*)malloc(1000*sizeof(char));
    pwd= getcwd(pwd,1000);
    printf("%s\n",pwd);
    free(pwd);
    return;
}