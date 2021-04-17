/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines xdup_strv_to_c
*/

#include "../shell_char.h"
#include "my/stdlib.h"

char **shell_char_xdup_strv_to_c(shell_char_t *const *strv)
{
    size_t vec_malloc_size = 1;
    char **result;

    for (shell_char_t *const *i = strv; *i != NULL; ++i)
        ++vec_malloc_size;
    result = my_xcalloc(1, vec_malloc_size * sizeof(*result));
    for (size_t i = 0; strv[i] != NULL; ++i)
        result[i] = shell_char_xstrdup_to_c(strv[i]);
    return result;
}
