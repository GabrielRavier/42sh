/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines main
*/

#include "shell.h"
#include "shell/init.h"
#include "shell/process.h"
#include "shell/exit_from_status.h"

int main(int argc, char *argv[])
{
    static struct shell self;

    (void)argc;
    shell_init(&self, argv[0]);
    shell_process(&self);
    shell_exit_from_status(&self);
}
