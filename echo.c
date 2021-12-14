#include "headers.h"

void echo(ll no_of_arg, char arg[][200])
{
    for (ll i = 1; i < no_of_arg; i++) //print all the arguments
    {
        printf("%s ", arg[i]);
    }
    printf("\n");
    return;
}