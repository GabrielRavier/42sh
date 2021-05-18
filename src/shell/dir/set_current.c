/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_current
*/

#include "../dir.h"
#include "../var.h"
#include <stdlib.h>

static const shell_char_t OWD[] = {'o', 'w', 'd', '\0'};
static const shell_char_t CWD[] = {'c', 'w', 'd', '\0'};

static bool set_vars(struct shell *self, const shell_char_t *cwd_name)
{
    if (!shell_var_set_val_dup(self, OWD, shell_var_get_value(self, CWD),
        VAR_FLAG_READ_WRITE | VAR_FLAG_NO_GLOB))
        return false;
    if (!shell_var_set_val_dup(self, CWD, cwd_name, VAR_FLAG_READ_WRITE |
        VAR_FLAG_NO_GLOB))
        return false;
    setenv("PWD", shell_char_static_xstrdup_to_c(cwd_name), 1);
    return true;
}

bool shell_dir_set_current(struct shell *self, struct dir *dir, int flags)
{
    self->current_dir = dir;
    if (!set_vars(self, self->current_dir->name))
        return false;
    if (self->force_print_directory_stack || (flags & SHELL_DIR_CMD_OPT_PRINT))
        shell_dir_print_stack(self, flags);
    return true;
}
