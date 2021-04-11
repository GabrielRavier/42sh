/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines init
*/

#include "init.h"
#include "my/my_string.h"
#include "my/string.h"
#include <unistd.h>

void shell_init(struct shell *self)
{
    self->input_fd = STDIN_FILENO;
    my_memset(self, 0, sizeof(*self));
    self->is_interactive = isatty(self->input_fd);
    lexical_word_list_init(&self->current_lexical_word);
}
