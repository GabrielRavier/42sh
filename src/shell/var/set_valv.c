/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines set_valv
*/

#include "../var.h"

void shell_var_set_valv(struct shell *self, const shell_char_t *var,
    shell_char_t **valv, int flags)
{
    struct var *var_i = &self->vars_head;
    struct var *var_j;
    int strcmp_result = 0;

    while (var_i->links[strcmp_result] != NULL) {
        var_j = var_i->links[strcmp_result];
        strcmp_result = shell_char_strcmp(var, var_j->name);
        if (strcmp_result == 0) {
            shell_char_strv_free(var_j->valv);
            var_j->flags = flags;
            var_j->valv = valv;
            shell_char_strv_unquote(var_j->valv);
            return;
        }
        var_i = var_j;
        strcmp_result = strcmp_result > 0;
    }
    var_i->links[strcmp_result] = my_xmalloc(sizeof(struct var));
    *var_i->links[strcmp_result] = (struct var){.name = shell_char_xstrdup(var),
        .flags = flags, .parent = var_i, .valv = valv};
    shell_char_strv_unquote(var_i->links[strcmp_result]->valv);
    var_tree_balance(var_i, strcmp_result);
}
