/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines internal stdio interfaces
*/

#pragma once

#include "my/stdio.h"
#include "my/stdlib.h"
#include <stdbool.h>

/// These are the functions used for normal FILE pointers, i.e. those made with
/// fopen that operate on file descriptors. This is here for extensability of
/// the FILE interface.
ssize_t my_internal_file_normal_read(void *internal_data, unsigned char *buffer,
    ssize_t count);
ssize_t my_internal_file_normal_write(void *internal_data,
    const unsigned char *buffer, ssize_t count);
my_fpos_t my_internal_file_normal_seek(void *internal_data, my_fpos_t offset,
    int whence);
int my_internal_file_normal_close(void *internal_data);

/// These are functions to work with the function pointers made to optimize them
/// better (they maintain fp->offset, etc.)
ssize_t my_internal_file_do_read(my_file_t *fp, unsigned char *buffer,
    ssize_t count);
ssize_t my_internal_file_do_write(my_file_t *fp, const unsigned char *buffer,
    ssize_t count);
my_fpos_t my_internal_file_do_seek(my_file_t *fp, my_fpos_t offset, int whence);

/// Parses the flags for the given mode, and stores the flags passed to open(2)
/// in *open_flags. Returns 0 if mode is invalid
int my_internal_file_parse_mode(const char *mode, int *open_flags);

/// Finds (or creates, if possible) a `my_file_t *` pointer for usage by the
/// fopen family
my_file_t *my_internal_file_find_ptr(void);

/// Writes c into fp's buffer (usually called when the buffer is full). The
/// buffer is flushed if it's full, or if the file is line buffered and c ==
/// '\n'
int my_internal_file_write_to_buffer(my_file_t *fp, int c);

/// Called by can_write when it has either a buffer not marked with FLAG_WRITE
/// or with a NULL buffer (and tries to correct those problems if possible)
bool my_internal_file_setup_write(my_file_t *fp);

/// Prepares the buffer for the file, i.e. either allocates a buffer and sets it
/// as the buffer for the file, or switches to non-buffered
void my_internal_file_make_buffer(my_file_t *fp);

/// Calls func for every open FILE, and returns the return value of every call
/// of func or-ed together
int my_internal_file_all_for_each(int (*func)(my_file_t *fp));

/// Same as fflush except fp can't be NULL and it ignores non-writeable files
int my_internal_file_flush_skip_non_write(my_file_t *fp);

/// Returns the flags that should be used for the given file relating to seek
/// optimization, stores the ideal buffer size in buffer_size and informs on
/// whether the file might be a tty in could_be_tty
int my_internal_file_determine_buffering(my_file_t *fp, size_t *buffer_size,
    bool *could_be_tty);

/// Cleans up my_file_t stuff. Needs to be referenced by the file implementing
/// g_my_standard_files to make sure everything using my_file_t ends up calling
/// this
void my_internal_file_cleanup(void);

/// Refills a buffer. Returns EOF on end of file or error and 0 otherwise
int my_internal_file_refill(my_file_t *fp);

#if !LIBMY_USE_LIBC_FILE

/// Returns whether we can write to the given file (it will also try to setup
/// for it if possible)
static inline bool my_internal_file_can_write(my_file_t *fp)
{
    return !(((fp->flags & MY_FILE_FLAG_WRITE) == 0 || (fp->buffer.base ==
        NULL)) && !my_internal_file_setup_write(fp));
}

/// Checks whether the given file has an active ungetc buffer
static inline bool my_internal_file_has_active_ungetc(my_file_t *fp)
{
    return fp->ungetc_buffer.base != NULL;
}

/// Frees an active ungetc buffer (note: does not do any other cleanup such as
/// restoring the ordinary unread data)
static inline void my_internal_file_free_ungetc_buffer(my_file_t *fp)
{
    if (fp->ungetc_buffer.base != fp->six_char_ungetc_buffer)
        my_free(fp->ungetc_buffer.base);
    fp->ungetc_buffer.base = NULL;
}

#endif
