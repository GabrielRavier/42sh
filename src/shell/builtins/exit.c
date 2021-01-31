/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin exit
*/

#include "functions.h"
#include "my/stdlib.h"
#include <stdlib.h>
#include <sys/wait.h>

int shell_builtin_exit(struct shell *self)
{
    exit(self->arguments[1] ? my_strtol(self->arguments[1], NULL, 10) : 0);
}
