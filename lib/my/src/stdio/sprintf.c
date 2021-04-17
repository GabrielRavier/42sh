/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines sprintf
*/

#include "my/stdio.h"

int my_sprintf(char *result_string, const char *format, ...)
{
    va_list arguments;
    int result;

    va_start(arguments, format);
    result = my_vsprintf(result_string, format, arguments);
    va_end(arguments);
    return result;
}
