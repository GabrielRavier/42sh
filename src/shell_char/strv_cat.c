/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv_cat
*/

#include "../shell_char.h"

shell_char_t **shell_char_strv_cat(shell_char_t **dest, shell_char_t **src)
{
    shell_char_strv_cpy(shell_char_strv_end_ncnst(dest), src);
    return dest;
}
