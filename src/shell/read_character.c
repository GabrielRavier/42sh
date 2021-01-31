/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines read_character
*/

#include "read_character.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int shell_read_character(struct shell *self)
{
    char result;

    if (read(STDIN_FILENO, &result, sizeof(result)) != sizeof(result))
        exit(self->last_child_exit_status);
    return (result);
}
