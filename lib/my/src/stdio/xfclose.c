/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xfclose
*/

#include "my/stdio.h"
#include "my/stdlib.h"
#include <unistd.h>

void my_xfclose(my_file_t *fp)
{
    if (my_ferror(fp)) {
        my_dputs("Tried to close file with pending errors\n", STDERR_FILENO);
        my__exit(84);
    }
    if (my_fflush(fp) != 0) {
        my_dputs("fflush failed\n", STDERR_FILENO);
        my__exit(84);
    }
    if (my_fclose(fp) != 0) {
        my_dputs("fclose failed\n", STDERR_FILENO);
        my__exit(84);
    }
}
