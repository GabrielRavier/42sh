/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines xstrndup
*/

#include "../shell_char.h"
#include "my/stdlib.h"
#include "my/string.h"

shell_char_t *shell_char_xstrndup(const shell_char_t *str, size_t len)
{
    shell_char_t *result = my_xmalloc(sizeof(*result) * (len + 1));

    my_memcpy(result, str, sizeof(*result) * len);
    result[len] = '\0';
    return result;
}
