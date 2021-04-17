/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines unlink
*/

#include "my/unistd.h"
#include <errno.h>

int my_unlink(MY_ATTR_UNUSED const char *pathname)
{
    errno = ENOSYS;
    return -1;
}
