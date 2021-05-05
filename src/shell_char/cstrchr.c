/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines cstrchr
*/

#include "../shell_char.h"

char *shell_char_cstrchr(const char *string, shell_char_t c)
{
    do {
        if ((shell_char_t)*string == c)
            return (char *)string;
    } while ((*string++) != '\0');
    return NULL;
}
