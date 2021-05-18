/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv_end
*/

#include "../shell_char.h"

const shell_char_t **shell_char_strv_end(const shell_char_t **strv)
{
    while (*strv != NULL)
        ++strv;
    return strv;
}
