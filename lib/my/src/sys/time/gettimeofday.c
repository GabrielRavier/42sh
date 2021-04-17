/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines gettimeofday
*/

#include "my/sys/time.h"
#include <errno.h>

int my_gettimeofday(struct timeval *tv, struct timezone *tz)
{
    (void)tv;
    (void)tz;
    errno = ENOSYS;
    return -1;
}
