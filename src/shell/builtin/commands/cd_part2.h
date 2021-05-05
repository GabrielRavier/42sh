/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part2 of cd
*/

#pragma once

#include "../../../shell.h"
#include "../../set_error.h"
#include "../../get_number.h"
#include "my/ctype.h"
#include <stdbool.h>

static inline bool find_from_plus_do_loop(struct shell *self, long long num_arg,
    struct dir **result)
{
    for (*result = self->current_dir; num_arg != 0; --num_arg) {
        *result = (*result)->prev;
        if (*result == &self->head_dir)
            *result = (*result)->prev;
        if (*result == self->current_dir) {
            shell_set_error(self, SHELL_ERROR_FLAG_NAME |
                SHELL_ERROR_DIRECTORY_STACK_NOT_THAT_DEEP);
            return false;
        }
    }
    return true;
}

static inline bool find_from_plus(struct shell *self,
    const shell_char_t *arg, struct dir **result)
{
    long long num_arg;

    *result = NULL;
    if (*arg++ != '+')
        return true;
    for (size_t i = 0; arg[i] != '\0'; ++i)
        if (!my_isdigit(arg[i]))
            return true;
    if (!shell_get_number(self, arg, &num_arg))
        return false;
    return num_arg <= 0 ? true : find_from_plus_do_loop(self, num_arg, result);
}
