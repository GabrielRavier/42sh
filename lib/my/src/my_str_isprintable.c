/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Check if the passed string only contains printable characters
*/

#include "my.h"

int my_str_isprintable(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        if (!my_isprint(str[i]))
            return (0);

    return (1);
}
