/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strcmp
*/

#include "../shell_char.h"

int shell_char_strcmp(const shell_char_t *string1,
    const shell_char_t *string2)
{
    size_t i = 0;

    do {
        if (string1[i] != string2[i])
            return string1[i] - string2[i];
    } while (string1[i++]);
    return 0;
}
