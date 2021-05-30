/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines unset
*/

#include "../var.h"
#include "../set_error.h"

bool shell_var_unset_name(struct shell *self, const shell_char_t *var)
{
    struct var *var_ptr = shell_var_get(self, var);

    if (var_ptr == NULL) {
        self->error_program_name = shell_char_static_xstrdup_to_c(var);
        shell_set_error(self, SHELL_ERROR_UNDEFINED_VARIABLE |
            SHELL_ERROR_FLAG_NAME);
        return false;
    }
    var_unset(var_ptr);
}
