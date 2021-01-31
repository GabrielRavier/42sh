/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin exit
*/

#include "functions.h"
#include <stdlib.h>
#include <sys/wait.h>

void shell_builtin_exit(struct shell *self)
{
    exit(0);
}
