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
    my_memset(self, 0, sizeof(*self));
    self->is_interactive = isatty(STDIN_FILENO);
}
