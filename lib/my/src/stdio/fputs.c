/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines fputs
*/

#include "my/stdio.h"

#if LIBMY_USE_LIBC_FILE

int my_fputs(const char *str, my_file_t *fp)
{
    return fputs(str, fp);
}
#else
int my_fputs(const char *str, my_file_t *fp)
{
    int result;

    while (*str != '\0')
        result = my_putc(*str++, fp);
    return result;
}
#endif
