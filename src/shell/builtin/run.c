/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines run
*/

#include "../builtin.h"
#include "../print_error.h"
#include "../set_error.h"

void shell_builtin_run(struct shell *self, const struct shell_builtin *builtin,
    struct shell_parse_tree *parse_tree)
{
    size_t arg_count = shell_char_strv_len_ncnst(parse_tree->argv) - 1;

    self->error_program_name = builtin->name;
    if (arg_count < builtin->min_arguments)
        shell_set_error(self, SHELL_ERROR_TOO_FEW_ARGUMENTS);
    if (arg_count > builtin->max_arguments)
        shell_set_error(self, SHELL_ERROR_TOO_MANY_ARGUMENTS);
    if (self->error.text == NULL)
        builtin->func(self, parse_tree->argv);
}
