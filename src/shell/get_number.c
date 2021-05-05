/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_number
*/

#include "get_number.h"
#include "set_error.h"
#include "my/ctype.h"
#include <stdbool.h>

static bool do_sign(struct shell *self, const shell_char_t **str, bool *sign)
{
    if (**str == '+' && (*str)[1] != '\0')
        ++*str;
    if (**str == '-') {
        *sign = true;
        ++str;
        if (!my_isdigit(**str)) {
            shell_set_error(self, SHELL_ERROR_FLAG_NAME |
                SHELL_ERROR_BADLY_FORMED_NUMBER);
            return false;
        }
    }
    return true;
}

bool shell_get_number(struct shell *self, const shell_char_t *str,
    long long *result)
{
    bool sign = false;

    *result = 0;
    if (str == NULL) {
        shell_set_error(self, SHELL_ERROR_FLAG_NAME |
            SHELL_ERROR_BADLY_FORMED_NUMBER);
        return false;
    }
    if (!do_sign(self, &str, &sign))
        return false;
    while (my_isdigit(*str))
        *result = *result * 10 + *str++ - '0';
    if (*str) {
        shell_set_error(self, SHELL_ERROR_FLAG_NAME |
            SHELL_ERROR_BADLY_FORMED_NUMBER);
        return false;
    }
    *result = sign ? -*result : *result;
    return true;
}
