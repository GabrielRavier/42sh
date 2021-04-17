/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines xstrdup
*/

#include "../shell_char.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <stddef.h>

shell_char_t *shell_char_xstrdup(const shell_char_t *string)
{
    const size_t string_length = shell_char_strlen(string) + 1;
    shell_char_t *const duplicate_string = my_xmalloc(string_length *
        sizeof(*duplicate_string));

    my_memcpy(duplicate_string, string, string_length * sizeof(*string));
    return duplicate_string;
}
