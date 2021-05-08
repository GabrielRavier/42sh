/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines vfprintf
*/

#include "my/stdio.h"
#include "my/stdlib.h"

int my_vfprintf(my_file_t *fp, const char *format, va_list arguments)
{
    char *string_to_print;
    const int string_length = my_vasprintf(&string_to_print, format, arguments);

    if (string_length < 0) {
        my_fseterr(fp);
        return -1;
    }
    if (my_fwrite(string_to_print, 1, (size_t)string_length, fp) !=
        (size_t)string_length) {
        my_free(string_to_print);
        return -1;
    }
    my_free(string_to_print);
    return string_length;
}
