/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines set_current
*/

#include "../dir.h"
#include "../var.h"
#include "my/stdlib.h"

static const shell_char_t OWD[] = {'o', 'w', 'd', '\0'};
static const shell_char_t CWD[] = {'c', 'w', 'd', '\0'};

static void set_vars(struct shell *self, const shell_char_t *cwd_name)
{
    shell_var_set_val_dup(self, OWD, shell_var_get_value(self, CWD),
        VAR_FLAG_READ_WRITE);
    shell_var_set_val_dup(self, CWD, cwd_name, VAR_FLAG_READ_WRITE);
    my_setenv("PWD", shell_char_static_xstrdup_to_c(cwd_name), 1);
}

void shell_dir_set_current(struct shell *self, struct dir *dir, int flags)
{
    self->current_dir = dir;
    set_vars(self, self->current_dir->name);
    if (self->force_print_directory_stack || (flags & SHELL_DIR_CMD_OPT_PRINT))
        shell_dir_print_stack(self, flags);
}
