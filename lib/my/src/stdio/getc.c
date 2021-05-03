/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines getc
*/

#include "my/stdio.h"
#include "my/internal/stdio.h"

#if LIBMY_USE_LIBC_FILE

my_file_t *my_getc(my_file_t *fp)
{
    return getc(fp);
}
#else
// When the buffer runs out, we refill it and return the first character from
// the now filled buffer
static int handle_buffer_empty(my_file_t *fp)
{
    if (my_internal_file_refill(fp) == 0) {
        --fp->read_space_left;
        return *fp->buffer_ptr++;
    }
    return EOF;
}

int my_getc(my_file_t *fp)
{
    return --fp->read_space_left < 0 ?
        handle_buffer_empty(fp) :
        (int)(*fp->buffer_ptr++);
}
#endif
