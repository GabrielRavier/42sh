/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fprintf
*/

#include "my/stdio.h"

int my_fprintf(my_file_t *fp, const char *restrict format, ...)
{
    va_list arguments;
    int result;

    va_start(arguments, format);
    result = my_vfprintf(fp, format, arguments);
    va_end(arguments);
    return result;
}
