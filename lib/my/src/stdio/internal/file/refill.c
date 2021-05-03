/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines refill
*/

#include "my/internal/stdio.h"
#include <errno.h>

#if !LIBMY_USE_LIBC_FILE

static int flush_line_buffered_file(my_file_t *fp)
{
    if ((fp->flags & (MY_FILE_FLAG_LINE_BUFFERED | MY_FILE_FLAG_WRITE)) ==
        (MY_FILE_FLAG_LINE_BUFFERED | MY_FILE_FLAG_WRITE))
        return my_internal_file_flush_skip_non_write(fp);
    return 0;
}

// Why we flush all line-buffered files on re-filling a non-buffered or
// line-buffered file: C Standard, Files, 7.21.3: When a stream is line
// buffered, characters are intended to be transmitted to or from the host
// environment as a block when [...] input is requested on an unbuffered stream,
// or when input is requested on a line buffered stream that requires the
// transmission of characters from the host environment.
static int do_after_read_check(my_file_t *fp)
{
    if (fp->buffer.base == NULL)
        my_internal_file_make_buffer(fp);
    if (fp->flags & (MY_FILE_FLAG_LINE_BUFFERED | MY_FILE_FLAG_NOT_BUFFERED)) {
        fp->flags |= MY_FILE_FLAG_ALL_FOR_EACH_IGNORE;
        my_internal_file_all_for_each(flush_line_buffered_file);
        fp->flags &= ~MY_FILE_FLAG_ALL_FOR_EACH_IGNORE;
        flush_line_buffered_file(fp);
    }
    fp->buffer_ptr = fp->buffer.base;
    fp->read_space_left = my_internal_file_do_read(fp, fp->buffer.base,
        fp->buffer.size);
    if (fp->read_space_left <= 0) {
        fp->flags |= (fp->read_space_left == 0) ? MY_FILE_FLAG_EOF :
            MY_FILE_FLAG_ERROR;
        fp->read_space_left = 0;
        return EOF;
    }
    return 0;
}

// Setting of read_space_left to 0 is largely done to make calling this more
// convenient
// If we aren't reading and this isn't a read-write file, we error, otherwise we
// switch to reading.
// We check for EOF first to conform to C99, which specifies that EOF must be
// returned from a read if the EOF indicator is set
int my_internal_file_refill(my_file_t *fp)
{
    fp->read_space_left = 0;
    if (fp->flags & MY_FILE_FLAG_EOF)
        return EOF;
    if (!(fp->flags & MY_FILE_FLAG_READ)) {
        if (!(fp->flags & MY_FILE_FLAG_READ_WRITE)) {
            errno = EBADF;
            fp->flags |= MY_FILE_FLAG_ERROR;
            return EOF;
        }
        if (fp->flags & MY_FILE_FLAG_WRITE) {
            if (my_internal_file_flush_skip_non_write(fp))
                return EOF;
            fp->flags &= ~MY_FILE_FLAG_WRITE;
            fp->write_space_left = 0;
            fp->line_buffer_size = 0;
        }
        fp->flags |= MY_FILE_FLAG_READ;
    }
    return do_after_read_check(fp);
}
#endif
