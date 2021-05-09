/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines my_vdprintf
*/

#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include <stdbool.h>

static bool do_write(int fd, const char *data, ssize_t n)
{
    ssize_t write_result;

    while (n > 0) {
        write_result = my_write(fd, data, n);
        if (write_result < 0)
            return false;
        n -= write_result;
        data += write_result;
    }
    return true;
}

int my_vdprintf(int fd, const char *format, va_list arguments)
{
    char *string_to_print;
    const int string_length = my_vasprintf(&string_to_print, format, arguments);
    bool result;

    if (string_length < 0)
        return -1;
    result = do_write(fd, string_to_print, string_length);
    my_free(string_to_print);
    return result ? string_length : -1;
}
