/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xstrndup
*/

#include "my/string.h"
#include "my/stdlib.h"

char *my_xstrndup(const char *string, size_t length)
{
    const size_t string_length = my_strnlen(string, length);
    char *const duplicate_string = (char *)my_xmalloc(string_length + 1);

    if (duplicate_string == NULL)
        return NULL;
    my_memcpy(duplicate_string, string, string_length);
    duplicate_string[string_length] = '\0';
    return duplicate_string;
}
