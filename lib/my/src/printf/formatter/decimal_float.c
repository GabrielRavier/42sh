/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_decimal_float
*/

#define _GNU_SOURCE
#include "my/internal/printf/formatter.h"
#include "my/my_string.h"
#include "my/string.h"
#include "my/math.h"
#include "my/ctype.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef LIBMY_FLOATING_POINT_CLUDGE
static struct my_string *make_format_string(
    struct my_printf_conversion_info *format_info)
{
    struct my_string *format_string = my_string_new_from_string("%", 1);
    if (format_info->flag_minus)
        my_string_append_char(format_string, '-');
    if (format_info->flag_plus)
        my_string_append_char(format_string, '+');
    if (format_info->flag_space)
        my_string_append_char(format_string, ' ');
    if (format_info->flag_hash)
        my_string_append_char(format_string, '#');
    if (format_info->flag_0)
        my_string_append_char(format_string, '0');
    asprintf_append_number_base(format_string, format_info->field_width, 10,
        false);
    if (format_info->precision != -1)
        asprintf_append_number_base(my_string_append_char(format_string, '.'),
            format_info->precision, 10, false);
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG_DOUBLE)
        my_string_append_char(format_string, 'L');
    my_string_append_char(format_string, format_info->conversion_specifier);
    return format_string;
}

struct my_string *asprintf_format_decimal_float(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    char *buffer;
    struct my_string *format_string = make_format_string(format_info);
    vasprintf(&buffer, format_string->string, arguments);
    if (buffer) {
        my_string_append(destination, buffer, my_strlen(buffer));
        free(buffer);
    }
    my_string_free(format_string);
    return (NULL);
}
#else

struct my_string *asprintf_format_decimal_float(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    (void)destination;
    (void)arguments;
    (void)format_info;
    return (NULL);
}
#endif
