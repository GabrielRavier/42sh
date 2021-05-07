/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines lfind
*/

#include "my/search.h"

void *my_lfind(const void *key, const void *base, size_t num_members,
    size_t element_size, int (*cmp)(const void *, const void *))
{
    char *end = (char *)base + num_members * element_size;

    for (char *i = (char *)base; i < end; i += element_size)
        if (cmp(key, i) == 0)
            return i;
    return NULL;
}
