/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xfopen
*/

#include "my/stdio.h"
#include "my/stdlib.h"
#include <unistd.h>

my_file_t *my_xfopen(const char *filename, const char *mode)
{
    my_file_t *result = my_fopen(filename, mode);

    if (result == NULL) {
        my_fprintf(my_stderr, "Could not open '%s' (mode '%s')\n",
            filename, mode);
        my_fflush(my_stderr);
        my__exit(84);
    }
    return result;
}
