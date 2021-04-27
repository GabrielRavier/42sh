/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines getpgrp
*/

#include "my/unistd.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include <unistd.h>

pid_t my_getpgrp(void)
{
    my_dputs("Tried to get process group but getpgrp is unavailable\n",
        STDERR_FILENO);
    my__exit(84);
}
