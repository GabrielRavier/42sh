/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines alloc_concat
*/

#include "../shell_char.h"
#include "my/stdlib.h"

static const shell_char_t NUL = '\0';

static void set_result(shell_char_t *result, const shell_char_t *left,
    const shell_char_t *right)
{
    *result = *left;
    while (*result != '\0')
        *++result = *++left;
    *result = *right;
    while (*result != '\0')
        *++result = *++right;
}

shell_char_t *shell_char_alloc_concat(const shell_char_t *left,
    const shell_char_t *right)
{
    const shell_char_t *left_end;
    const shell_char_t *right_end;
    shell_char_t *result;

    if (left == NULL)
        left = &NUL;
    if (right == NULL)
        right = &NUL;
    for (left_end = left; *left_end++ != '\0';)
        ;
    for (right_end = right; *right_end++ != '\0';)
        ;
    result = my_xmalloc(sizeof(*result) * ((left_end - left) + (right_end -
        right) - 1));
    set_result(result, left, right);
    return result;
}
