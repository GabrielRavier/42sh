/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines ungetc
*/

#include "my/internal/stdio.h"
#include "my/stdio.h"
#include "ungetc_part2.h"

#if LIBMY_USE_LIBC_FILE

int my_ungetc(int c, my_file_t *fp)
{
    return ungetc(c, fp);
}
#else
// If we already have ungetc-ed characters, just push back onto there
int my_ungetc(int c, my_file_t *fp)
{
    if (c == EOF || !switch_if_not_read(fp))
        return EOF;
    c = (unsigned char)c;
    if (my_internal_file_has_active_ungetc(fp)) {
        if (fp->read_space_left >= fp->ungetc_buffer.size && !expand_buffer(fp))
            return EOF;
        *--fp->buffer_ptr = c;
        ++fp->read_space_left;
        return c;
    }
    return do_non_active_ungetc(fp, c);
}
#endif
