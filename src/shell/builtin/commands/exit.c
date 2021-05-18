/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines builtin exit
*/

#include "../commands.h"
#include "../../input_set_eof.h"
#include "my/stdlib.h"
#include <unistd.h>

void shell_builtin_exit(struct shell *self, shell_char_t **argv)
{
    if (argv[1] != NULL)
        self->last_command_exit_status = my_strtol(
            shell_char_static_xstrdup_to_c(argv[1]), NULL, 10);
    shell_input_set_eof(self);
    close(self->input_fd);
}
