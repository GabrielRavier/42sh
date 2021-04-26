/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines strv_dup
*/

#include "../shell_char.h"
#include "my/stdlib.h"

shell_char_t **shell_char_strv_dup(const shell_char_t **strv)
{
    shell_char_t **result;

    if (strv == NULL)
        return NULL;
    result = my_xcalloc(shell_char_strv_len(strv) + 1, sizeof(*result));
    for (size_t i = 0; strv[i] != NULL; ++i)
        result[i] = shell_char_xstrdup(strv[i]);
    return result;
}
