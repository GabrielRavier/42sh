/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strcmp_ignore_quote
*/

#include "../shell_char.h"

int shell_char_cstrcmp_ignore_quote(const shell_char_t *string1,
    const char *string2)
{
    size_t i = 0;

    do {
        if (string1[i] != (unsigned char)string2[i])
            return string1[i] - (unsigned char)string2[i];
    } while (string1[i++]);
    return 0;
}
