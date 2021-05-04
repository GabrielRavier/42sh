/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines ungetc
*/

#include "my/internal/stdio.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"

#if LIBMY_USE_LIBC_FILE

int my_ungetc(int c, my_file_t *fp)
{
    return ungetc(c, fp);
}
#else
/// This is for when we want to get a new buffer, rather than expanding the old
/// one
static bool expand_six_char_ungetc_buffer(my_file_t *fp)
{
    unsigned char *new_buffer = my_malloc(BUFSIZ);

    if (new_buffer == NULL)
        return false;
    fp->ungetc_buffer.base = new_buffer;
    fp->ungetc_buffer.size = BUFSIZ;
    new_buffer += BUFSIZ - sizeof(fp->ungetc_buffer);
    my_memcpy(new_buffer, fp->six_char_ungetc_buffer, sizeof(
        fp->six_char_ungetc_buffer));
    fp->buffer_ptr = new_buffer;
    return true;
}

// We try here to expand the ungetc buffer. This will also adjust fp->buffer_ptr
// to make it point to the same place within the buffer even if we have to
// reallocate it, and reorganize the contents of the buffer to make all seem as
// normal.
static bool expand_buffer(my_file_t *fp)
{
    unsigned char *new_buffer;

    if (fp->ungetc_buffer.base == fp->six_char_ungetc_buffer)
        return expand_six_char_ungetc_buffer(fp);
    new_buffer = my_realloc_size(fp->ungetc_buffer.base,
        fp->ungetc_buffer.size << 1, fp->ungetc_buffer.size);
    if (new_buffer == NULL)
        return EOF;
    my_memcpy(new_buffer + fp->ungetc_buffer.size, new_buffer,
        fp->ungetc_buffer.size);
    fp->buffer_ptr = new_buffer + fp->ungetc_buffer.size;
    fp->ungetc_buffer.base = new_buffer;
    fp->ungetc_buffer.size <<= 1;
    return true;
}

// If we're not reading, that's invalid unless we're reading *and* writing, in
// which case we switch
static bool switch_if_not_read(my_file_t *fp)
{
    if (!(fp->flags & MY_FILE_FLAG_READ)) {
        if (!(fp->flags & MY_FILE_FLAG_READ_WRITE))
            return false;
        if (fp->flags & MY_FILE_FLAG_WRITE) {
            if (my_internal_file_flush_skip_non_write(fp))
                return false;
            fp->flags &= ~MY_FILE_FLAG_WRITE;
            fp->write_space_left = 0;
            fp->line_buffer_size = 0;
        }
        fp->flags |= MY_FILE_FLAG_READ;
    }
    return true;
}

static int do_non_active_ungetc(my_file_t *fp, int c)
{
    fp->flags &= ~MY_FILE_FLAG_EOF;
    if (fp->buffer.base != NULL && fp->buffer_ptr > fp->buffer.base &&
        fp->buffer_ptr[-1] == c) {
        --fp->buffer_ptr;
        ++fp->read_space_left;
        return c;
    }
    fp->ungetc_saved_read_space_left = fp->read_space_left;
    fp->ungetc_saved_buffer_ptr = fp->buffer_ptr;
    fp->ungetc_buffer.base = fp->six_char_ungetc_buffer;
    fp->ungetc_buffer.size = sizeof(fp->six_char_ungetc_buffer);
    fp->buffer_ptr = &fp->ungetc_buffer.base[fp->ungetc_buffer.size - 1];
    *fp->buffer_ptr = c;
    fp->read_space_left = 1;
    return c;
}

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
