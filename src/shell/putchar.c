/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines putchar
*/

#include "putchar.h"
#include "flush_output_buffer.h"

void shell_putchar(struct shell *self, shell_char_t character)
{
    character &= SHELL_CHAR_NOT_QUOTE;
    *self->line_buffer_current_ptr++ = character;
    if (self->line_buffer_current_ptr == &self->line_buffer[sizeof(
        self->line_buffer) - 1] || character == '\n')
        shell_flush_output_buffer(self);
}
