/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines error
*/

#include "error.h"
#include "my/stdio.h"
#include <unistd.h>

void error(const char *string)
{
    my_dputs(string, STDERR_FILENO);
    my_dputc('\n', STDERR_FILENO);
}
