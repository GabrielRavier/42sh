/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_valv
*/

#include "../var.h"
#include "set_valv_part2.h"
#include "../glob.h"
#include "../set_error.h"

static void do_raw_set(struct shell *self, const shell_char_t *var,
    shell_char_t **valv, int flags)
{
    struct var *var_i = &self->vars_head;
    int strcmp_result = 0;

    if (do_loop(&((struct dl_opts_t){var, valv, flags, &strcmp_result,
        &var_i})))
        return;
    var_i->links[strcmp_result] = my_xmalloc(sizeof(struct var));
    *var_i->links[strcmp_result] = (struct var){.name = shell_char_xstrdup(var),
        .flags = flags, .parent = var_i, .valv = valv};
    shell_char_strv_unquote(var_i->links[strcmp_result]->valv);
    var_tree_balance(var_i, strcmp_result, false);
}

bool shell_var_set_valv(struct shell *self, const shell_char_t *var,
    shell_char_t **valv, int flags)
{
    shell_char_t **orig_valv = valv;
    int glob_flags;

    if (!(flags & VAR_FLAG_NO_GLOB)) {
        glob_flags = shell_glob_strv_get_flags_ncnst(orig_valv);
        if (glob_flags) {
            if (!shell_glob_strv_all_ncnst(self, orig_valv, glob_flags, &valv))
                return false;
            shell_char_strv_free(orig_valv);
            if (valv == NULL) {
                shell_set_error(self, SHELL_ERROR_FLAG_NAME |
                    SHELL_ERROR_NO_MATCH);
                return false;
            }
        }
    }
    do_raw_set(self, var, valv, flags);
    return true;
}
