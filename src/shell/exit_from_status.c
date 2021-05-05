/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines exit_from_status
*/

#include "exit_from_status.h"
#include "exit.h"
#include "my/assert.h"

// We make sure child_depth is set so that this will *always* exit
void shell_exit_from_status(struct shell *self)
{
    self->child_depth = 1;
    shell_exit(self, self->last_command_exit_status);
}
