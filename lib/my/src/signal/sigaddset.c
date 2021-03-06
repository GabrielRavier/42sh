/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines sigaddset
*/

#include "my/signal.h"
#include <errno.h>
#include <limits.h>

static const size_t ULONG_WIDTH = sizeof(unsigned long) * CHAR_BIT;

// Assumes glibc's sigset_t is used
int my_sigaddset(sigset_t *set, int signum)
{
    if (signum <= 0 || signum >= NSIG) {
        errno = EINVAL;
        return -1;
    }
    set->__val[(signum - 1) / ULONG_WIDTH] |=
        (1ULL << ((signum - 1) % ULONG_WIDTH));
    return 0;
}
