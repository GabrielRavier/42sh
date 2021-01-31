/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin cd
*/

#include "functions.h"
#include "my/stdlib.h"
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

void shell_builtin_cd(struct shell *self)
{
    if ((self->arguments[1] != NULL || my_getenv("HOME") != NULL) &&
        (chdir(self->arguments[1] ?: my_getenv("HOME")) != 0))
        perror("cd");
}
