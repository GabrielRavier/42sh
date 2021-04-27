/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines xstrdup_from_c
*/

#include "../shell_char.h"
#include "my/stdlib.h"
#include "my/string.h"

shell_char_t *shell_char_xstrdup_from_c(const char *string)
{
    const size_t string_length = my_strlen(string) + 1;
    shell_char_t *const duplicate_string = my_xmalloc(string_length * sizeof(
        *duplicate_string));

    for (size_t i = 0; i < string_length; ++i)
        duplicate_string[i] = string[i];
    return duplicate_string;
}
