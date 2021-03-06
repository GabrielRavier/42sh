/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines flush
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"
#include <errno.h>

#if LIBMY_USE_LIBC_FILE

int my_fflush(my_file_t *fp)
{
    return fflush(fp);
}
#else
// SUSv3 says we return 0 for the non-write case
int my_fflush(my_file_t *fp)
{
    if (fp == NULL)
        return my_internal_file_all_for_each(
            my_internal_file_flush_skip_non_write);
    if (!(fp->flags & (MY_FILE_FLAG_WRITE | MY_FILE_FLAG_READ_WRITE)))
        return 0;
    return my_internal_file_flush_skip_non_write(fp);
}
#endif
