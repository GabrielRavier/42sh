/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines clearerr
*/

#include "my/stdio.h"

#if LIBMY_USE_LIBC_FILE

void my_clearerr(my_file_t *fp)
{
    clearerr(fp);
}
#else
void my_clearerr(my_file_t *fp)
{
    fp->flags &= ~(MY_FILE_FLAG_ERROR | MY_FILE_FLAG_EOF);
}
#endif
