/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares sys/time-related entities
*/

#pragma once

#include "my/features.h"
#include <sys/time.h>

// Gets the current time as a timeval as well as the timezone
int my_gettimeofday(struct timeval *MY_RESTRICT tv,
    struct timezone *MY_RESTRICT tz) MY_ATTR_NOTHROW MY_ATTR_NONNULL((1));
