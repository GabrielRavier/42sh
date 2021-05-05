/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines main
*/

#include "shell.h"
#include "shell/init.h"
#include "shell/process.h"
#include "shell/exit_from_status.h"
#include "shell/print_error.h"

int main(int argc, char *argv[])
{
    static struct shell self;

    (void)argc;
    if (!shell_init(&self, argv[0])) {
        ++self.child_depth;
        shell_print_error(&self);
    }
    shell_process(&self);
    shell_exit_from_status(&self);
}
