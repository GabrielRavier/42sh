/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines strrchr
*/

#include "my/string.h"

char *my_strrchr(const char *str, int character)
{
    char as_char = character;

    for (char *result = NULL;; ++str) {
        if (*str == as_char)
            result = (char *)str;
        if (*str == '\0')
            return result;
    }
}
