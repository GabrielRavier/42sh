/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines strncmp
*/

#include "my/string.h"

int my_strncmp(const char *string1, const char *string2, size_t n)
{
    size_t i = 0;

    do {
        if (n == 0)
            return 0;
        if (string1[i] != string2[i])
            return string1[i] - string2[i];
        --n;
    } while (string1[i++]);
    return 0;
}
