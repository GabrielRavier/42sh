/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xstrdup
*/

#include "my/string.h"
#include "my/stdlib.h"

char *my_xstrdup(const char *string)
{
    const size_t string_length = my_strlen(string) + 1;
    void *const duplicate_string = my_xmalloc(string_length);

    if (!duplicate_string)
        return NULL;
    my_memcpy(duplicate_string, string, string_length);
    return (char *)duplicate_string;
}
