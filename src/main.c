/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines main
*/

#include "shell.h"
#include "shell/get_character.h"
#include "shell/do_line.h"
#include "shell/init.h"
#include "my/stdio.h"
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

int main(void)
{
    struct shell self;

    shell_init(&self);
    if (self.is_interactive) {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, SIG_IGN);
    }
    while (true) {
        if (self.is_interactive)
            my_dputs("$> ", STDOUT_FILENO);
        self.peek_character = shell_get_character(&self);
        shell_do_line(&self);
    }
    return (self.last_child_status);
}
