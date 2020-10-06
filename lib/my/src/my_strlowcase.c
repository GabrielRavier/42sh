/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Puts every letter of a string into lowercase
*/

#include "my.h"

char *my_strlowcase(char *str)
{
    char *result = str;

    while (*str != '\0') {
        *str = my_tolower(*str);
        ++str;
    }

    return (result);
}
