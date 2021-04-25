/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines run
*/

#include "../builtin.h"
#include "../print_error.h"
#include "../set_error.h"

void shell_builtin_run(struct shell *self, const struct shell_builtin *builtin,
    struct shell_parse_tree *parse_tree)
{
    size_t args = -1;

    self->error_program_name = builtin->name;
    for (shell_char_t **i = parse_tree->argv; *i != NULL; ++i)
        ++args;
    if (args < builtin->min_arguments)
        shell_set_error(self, SHELL_ERROR_TOO_FEW_ARGUMENTS);
    if (args > builtin->max_arguments)
        shell_set_error(self, SHELL_ERROR_TOO_MANY_ARGUMENTS);
    if (!self->error) {
        builtin->func(self, parse_tree->argv);
        self->last_command_exit_status = (self->error != NULL);
    } else
        shell_print_error(self);
}
