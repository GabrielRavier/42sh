/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xcalloc
*/

#include "my/stdlib.h"
#include "my/string.h"

void *my_xcalloc(size_t num_members, size_t size)
{
    size_t malloc_size = num_members * size;
    void *result = my_xmalloc(malloc_size);

    my_memset(result, 0, malloc_size);
    return result;
}

