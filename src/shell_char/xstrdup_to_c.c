/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines xstrdup_to_c
*/

#include "../shell_char.h"
#include "my/stdlib.h"

char *shell_char_xstrdup_to_c(const shell_char_t *string)
{
    const size_t string_length = shell_char_strlen(string) + 1;
    char *const duplicate_string = my_xmalloc(string_length);

    for (size_t i = 0; i < string_length; ++i)
        duplicate_string[i] = string[i];
    return duplicate_string;
}
