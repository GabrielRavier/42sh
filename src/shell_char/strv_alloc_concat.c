/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv_alloc_concat
*/

#include "../shell_char.h"
#include "my/stdlib.h"

shell_char_t **shell_char_strv_alloc_concat(shell_char_t **left,
    shell_char_t **right)
{
    shell_char_t **result = my_xcalloc(shell_char_strv_len_ncnst(left) +
        shell_char_strv_len_ncnst(right) + 1, sizeof(*result));

    shell_char_strv_cpy(result, left);
    shell_char_strv_cat(result, right);
    return result;
}
