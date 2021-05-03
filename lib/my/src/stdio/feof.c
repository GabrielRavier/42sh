/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines feof
*/

#include "my/stdio.h"
#include <stdbool.h>

#if LIBMY_USE_LIBC_FILE

int my_feof(my_file_t *fp)
{
    return feof(fp);
}
#else
int my_feof(my_file_t *fp)
{
    return (bool)(fp->flags & MY_FILE_FLAG_EOF);
}
#endif
