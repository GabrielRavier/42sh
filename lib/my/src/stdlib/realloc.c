/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines realloc
*/

#include "my/stdlib.h"
#include <stdlib.h>
#include <errno.h>

#if LIBMY_HAS_LIBC_REALLOC

void *my_realloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}
#else
void *my_realloc(MY_ATTR_UNUSED void *ptr, MY_ATTR_UNUSED size_t size)
{
    errno = ENOSYS;
    return NULL;
}
#endif
