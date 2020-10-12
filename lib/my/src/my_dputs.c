/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Writes the string s to fd (without its null terminator)
*/

#include "my.h"
#include <unistd.h>

void my_dputs(const char *string, int fd)
{
    if (*string == '\0')
        return;

    write(fd, string, my_strlen(string));
}
