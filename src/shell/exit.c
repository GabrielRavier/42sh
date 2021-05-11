/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines exit
*/

#include "exit.h"
#include "my/assert.h"
#include "my/stdlib.h"

void shell_exit(struct shell *self, int status)
{
    (void)self;
    my__exit(status);
}