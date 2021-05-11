/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xmalloc
*/

#include "my/stdlib.h"
#include "my/stdio.h"
#include <unistd.h>

void *my_xmalloc(size_t size)
{
    void *result = my_malloc(size);

    if (result == NULL) {
        my_fprintf(my_stderr, "Out of memory while trying to allocate %zu "
            "bytes\n", size);
        my_fflush(my_stderr);
        my__exit(84);
    }
    return result;
}
