/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines exit
*/

#include "exit.h"
#include <stdlib.h>

void shell_exit(struct shell *self, int status)
{
    (void)self;
    exit(status);
}
