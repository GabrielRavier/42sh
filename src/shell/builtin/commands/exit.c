/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines builtin exit
*/

#include "../commands.h"
#include "../../exit.h"
#include "my/stdlib.h"
#include <stdlib.h>
#include <sys/wait.h>

void shell_builtin_exit(struct shell *self, shell_char_t **argv)
{
    (void)self;
    shell_exit(self, argv[1] ? my_strtol(shell_char_xstrdup_to_c(argv[1]),
        NULL, 10) : 0);
}
