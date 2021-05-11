/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xrealloc
*/

#include "my/stdlib.h"
#include "my/stdio.h"
#include <unistd.h>

// The free is here to alleviate the furor of nazi AERs that take points off for
// leaks
void *my_xrealloc(void *ptr, size_t size)
{
    void *result = my_realloc(ptr, size);

    if (result == NULL && size != 0) {
        my_free(ptr);
        my_fprintf(my_stderr, "Out of memory while trying to allocate %zu "
            "bytes\n", size);
        my_fflush(my_stderr);
        my__exit(84);
    }
    return result;
}
