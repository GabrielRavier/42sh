/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fseterr
*/

#include "my/stdio.h"

#if LIBMY_USE_LIBC_FILE

// This implementation assumes glibc is used
void my_fseterr(my_file_t *fp)
{
    fp->_flags |= _IO_ERR_SEEN;
}
#else
void my_fseterr(my_file_t *fp)
{
    fp->flags |= MY_FILE_FLAG_ERROR;
}
#endif
