/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines main
*/

#include "shell.h"
#include "shell/init.h"
#include "shell/process.h"

int main(void)
{
    static struct shell self;

    shell_init(&self);
    shell_process(&self);
    return (self.last_command_exit_status);
}
