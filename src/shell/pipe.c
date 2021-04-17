/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines pipe
*/

#include "pipe.h"
#include "set_error.h"
#include "print_error.h"
#include <unistd.h>

void shell_pipe(struct shell *self, int pipefd[2])
{
    if (pipe(pipefd) < 0) {
        shell_set_error(self, SHELL_ERROR_CANT_MAKE_PIPE);
        shell_print_error(self, true);
    }
}
