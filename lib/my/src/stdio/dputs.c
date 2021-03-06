/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines dputs
*/

#include "my/stdio.h"
#include "my/string.h"
#include "my/unistd.h"
#include <stdio.h>

int my_dputs(const char *string, int fd)
{
    const size_t string_len = my_strlen(string);

    if (string_len == 0)
        return 0;
    if ((size_t)my_write(fd, string, string_len) != string_len)
        return EOF;
    return 0;
}
