/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xrealloc
*/

#include "my/stdlib.h"
#include "my/stdio.h"
#include <unistd.h>

void *my_xrealloc(void *ptr, size_t size)
{
    void *result = my_realloc(ptr, size);

    if (result == NULL && size != 0) {
        my_free(ptr);
        my_dprintf(STDERR_FILENO, "Out of memory while trying to allocate %zu "
            "bytes\n", size);
        my__exit(84);
    }
    return result;
}
