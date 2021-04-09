/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines new_from_filename
*/

#include "my/my_string.h"
#include "my/unistd.h"
#include "my/fcntl.h"
#include "my/sys/stat.h"
#include <fcntl.h>

struct my_string *my_string_new_from_filename(const char *filename)
{
    int fd = my_open(filename, O_RDONLY);
    struct my_string *result;
    struct stat stat_buffer;

    if (fd < 0)
        return (NULL);
    if (my_fstat(fd, &stat_buffer) < 0 || stat_buffer.st_size < 0) {
        my_close(fd);
        return (NULL);
    }
    result = my_string_new();
    my_string_resize(result, stat_buffer.st_size);
    if (my_read(fd, result->string, result->length) < (ssize_t)result->length) {
        my_close(fd);
        my_string_free(result);
        return (NULL);
    }
    my_close(fd);
    return (result);
}
