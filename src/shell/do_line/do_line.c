/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines do_line
*/

#include "../do_line.h"
#include "word.h"
#include "../execute.h"
#include "my/my_string.h"

void shell_do_line(struct shell *self)
{
    char *current_ptr;

    self->line_ptr = self->line;
    self->end_line_ptr = self->line + LINE_STATE_LINE_SIZE - 1;
    self->arguments_ptr = self->arguments;
    self->end_arguments_ptr = self->arguments + LINE_STATE_ARGUMENTS_SIZE - 1;
    self->has_errored = false;
    do {
        current_ptr = self->line_ptr;
        shell_do_line_word(self);
    } while (*current_ptr != '\n');
    if (!self->has_errored) {
        if (self->arguments_ptr != self->arguments)
            self->arguments_ptr[-1] = NULL;
        if (self->arguments[0])
            shell_do_line_execute(self);
    }
}
