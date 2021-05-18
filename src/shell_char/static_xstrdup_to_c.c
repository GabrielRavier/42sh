/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines static_xstrdup_to_c
*/

#include "../shell_char.h"
#include "../char_vector.h"
#include "my/stdlib.h"

char *shell_char_static_xstrdup_to_c(const shell_char_t *string)
{
    static struct my_char_vector *result = NULL;

    if (result == NULL)
        result = my_char_vector_new();
    my_char_vector_resize(result, 0);
    while (*string)
        my_char_vector_append_single(result, *string++);
    my_char_vector_append_single(result, '\0');
    return result->data;
}
