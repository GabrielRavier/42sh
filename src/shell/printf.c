/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines printf
*/

#include "printf.h"
#include "putchar.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <stdarg.h>

void shell_printf(struct shell *self, const char *format, ...)
{
    va_list arg_list;
    char *vasprintf_result;

    va_start(arg_list, format);
    my_xvasprintf(&vasprintf_result, format, arg_list);
    va_end(arg_list);
    for (size_t i = 0; vasprintf_result[i] != '\0'; ++i)
        shell_putchar(self, vasprintf_result[i]);
    my_free(vasprintf_result);
}
