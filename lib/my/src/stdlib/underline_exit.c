/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines _exit
*/

#include "my/stdlib.h"
#include "my/stdio.h"
#include <unistd.h>

#if LIBMY_HAS_LIBC__EXIT

void my__exit(int status)
{
    _exit(status);
}
#else
void my__exit(int status)
{
    my_fprintf(my_stderr, "Tried to _exit with status %d but _exit not "
        "available. Aborting...\n", status & 0xFF);
    my_fflush(my_stderr);
    my_abort();
}
#endif
