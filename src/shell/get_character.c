/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines get_character
*/

#include "get_character.h"
#include "read_character.h"
#include "../error.h"

static char do_args_error(struct shell *self)
{
    char c;

    self->arguments_ptr -= 10;
    do
        c = shell_get_character(self);
    while (c != '\n');
    self->arguments_ptr += 10;
    error("Too many arguments");
    self->has_errored = true;
    return ('\n');
}

static char do_line_error(struct shell *self)
{
    char c;

    self->line_ptr -= 10;
    do
        c = shell_get_character(self);
    while (c != '\n');
    error("Too many characters");
    self->has_errored = true;
    return ('\n');
}

char shell_get_character(struct shell *self)
{
    char result;

    if (self->peek_character) {
        result = self->peek_character;
        self->peek_character = 0;
        return (result);
    }
    if (self->arguments_ptr > self->end_arguments_ptr)
        return (do_args_error(self));
    if (self->line_ptr > self->end_line_ptr)
        return (do_line_error(self));
    result = shell_read_character(self);
    if (result == '\\') { 
        result = shell_read_character(self);
        if (result == '\n')
            return (' ');
    }
    return (result);
}
