/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines input_set_eof
*/

#include "input_set_eof.h"
#include "my/unistd.h"
#include <unistd.h>
#include <sys/types.h>

void shell_input_set_eof(struct shell *self)
{
    my_lseek(self->input_fd, 0, SEEK_END);
}
