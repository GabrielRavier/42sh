/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines xvasprintf
*/

#include "my/stdio.h"
#include "my/stdlib.h"
#include <unistd.h>

int my_xvasprintf(char **result_string_ptr, const char *format,
    va_list arguments)
{
    int result = my_vasprintf(result_string_ptr, format, arguments);

    if (result < 0) {
        my_dputs("my_vasprintf failed, most likely out of memory\n",
            STDERR_FILENO);
        my__exit(84);
    }
    return result;
}
