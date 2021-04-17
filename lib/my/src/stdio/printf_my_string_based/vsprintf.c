/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines vsprintf
*/

#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"

int my_vsprintf(char *result_string, const char *format, va_list arguments)
{
    char *tmp_str;
    const int vasprintf_result = my_vasprintf(&tmp_str, format, arguments);

    if (vasprintf_result < 0)
        return -1;
    my_memcpy(result_string, tmp_str, (size_t)vasprintf_result + 1);
    my_free(tmp_str);
    return vasprintf_result;
}
