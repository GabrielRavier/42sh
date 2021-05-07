/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines puts
*/

#include "my/stdio.h"
#include <stdio.h>
#include <unistd.h>

int my_puts(const char *string)
{
    my_fputs(string, my_stdout);
    return my_putc('\n', my_stdout);
}
