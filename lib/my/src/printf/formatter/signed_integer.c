/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_format_signed_integer
*/

#include "my/internal/printf/formatter.h"
#include <limits.h>

static intmax_t get_arg(va_list arguments,
    struct my_printf_conversion_info *format_info)
{
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG)
        return va_arg(arguments, long);
    return va_arg(arguments, int);
}

// Note: The cast to uintptr_t (done explicitly here for clarity) will handle
// the issue of INTMAX_MIN, since casting that to uintptr_t on 2s complement
// (now mandatory in C2x) will result in the corresponding unsigned value
void asprintf_format_signed_integer(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    intmax_t signed_argument = get_arg(arguments, format_info);

    if (signed_argument < 0) {
        my_string_append_char(destination, '-');
        if (signed_argument != INTMAX_MIN)
            signed_argument = -signed_argument;
    }
    asprintf_append_number_base(destination, (uintmax_t)signed_argument, 10,
        false);
}

