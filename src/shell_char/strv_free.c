/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv_free
*/

#include "../shell_char.h"
#include "my/stdlib.h"

void shell_char_strv_free(shell_char_t **strv)
{
    if (strv == NULL)
        return;
    for (shell_char_t **i = strv; *i != NULL; ++i)
        my_free(*i);
    my_free(strv);
}
