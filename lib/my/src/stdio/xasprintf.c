/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xasprintf
*/

#include "my/stdio.h"

int my_xasprintf(char **result_string_ptr, const char *format, ...)
{
    va_list arguments;
    int result;

    va_start(arguments, format);
    result = my_xvasprintf(result_string_ptr, format, arguments);
    va_end(arguments);
    return result;
}
