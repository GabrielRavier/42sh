/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines init
*/

#include "../init.h"
#include "my/string.h"
#include <unistd.h>
#include <signal.h>

void shell_init(struct shell *self)
{
    my_memset(self, 0, sizeof(*self));
    shell_init_fds(self);
    self->input_is_tty = isatty(self->input_fd);
    self->parent_sigint_handler = signal(SIGINT, SIG_IGN);
    signal(SIGINT, self->parent_sigint_handler);
    self->should_set_interrupts = (self->input_is_tty &&
        isatty(self->output_fd)) || self->parent_sigint_handler == SIG_DFL;
    lexical_word_list_init(&self->current_lexical_word);
}
