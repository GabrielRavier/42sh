/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines read_character
*/

#include "read_character.h"
#include "exit_from_status.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

shell_char_t shell_read_character(struct shell *self, bool want_eof)
{
    char read_result;
    shell_char_t peek_read_result;

    if (self->peek_read != 0) {
        peek_read_result = self->peek_read;
        self->peek_read = 0;
        return peek_read_result;
    }
    do
        if (read(self->input_fd, &read_result, sizeof(read_result)) !=
            sizeof(read_result)) {
            if (want_eof)
                return SHELL_CHAR_ERROR;
            shell_exit_from_status(self);
        }
    while (read_result == 0);
    return read_result;
}
