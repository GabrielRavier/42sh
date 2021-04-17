/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines getpid
*/

#include "my/unistd.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include <unistd.h>

#if LIBMY_HAS_LIBC_GETPID

pid_t my_getpid(void)
{
    return getpid();
}
#else
pid_t my_getpid(void)
{
    my_dputs("Tried to get pid but getpid is unavailable", STDERR_FILENO);
    my__exit(84);
}
#endif

