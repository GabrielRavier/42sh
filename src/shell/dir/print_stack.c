/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines print_stack
*/

#include "../dir.h"
#include "my/stdio.h"

void shell_dir_print_stack(struct shell *self, int flags)
{
    struct dir *dir_i = self->current_dir;
    size_t i = 0;

    do {
        if (dir_i == &self->head_dir) {
            dir_i = dir_i->prev;
            continue;
        }
        if (flags & SHELL_DIR_CMD_OPT_VERTICAL)
            my_dprintf(self->output_fd, "%zu\t", i++);
        my_dprintf(self->output_fd, "%-s%c", shell_char_static_xstrdup_to_c(
            dir_i->name), (flags & SHELL_DIR_CMD_OPT_VERTICAL) ? '\n' : ' ');
        dir_i = dir_i->prev;
    } while (dir_i != self->current_dir);
    if (!(flags & SHELL_DIR_CMD_OPT_VERTICAL))
        my_dputc('\n', self->output_fd);
}
