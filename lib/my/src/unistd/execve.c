/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines execve
*/

#include "my/unistd.h"
#include <unistd.h>
#include <errno.h>

#if LIBMY_HAS_LIBC_EXECVE

int my_execve(const char *pathname, char *const argv[], char *const envp[])
{
    return execve(pathname, argv, envp);
}
#else
int my_execve(const char *pathname MY_ATTR_UNUSED,
    char *const argv[] MY_ATTR_UNUSED, char *const envp[] MY_ATTR_UNUSED)
{
    errno = ENOSYS;
    return -1;
}
#endif
