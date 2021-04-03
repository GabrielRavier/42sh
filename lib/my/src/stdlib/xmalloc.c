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
        my_dprintf(STDERR_FILENO, "Out of memory while trying to allocate %zu "
            "bytes\n", size);
        my__exit(84);
    }
    return result;
}
