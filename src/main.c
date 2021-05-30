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
#include "shell/signal.h"
#include "shell/printf.h"

static void do_fatal(struct shell *self)
{
    ++self->child_depth;
    shell_print_error(self);
}

int main(int argc, char *argv[])
{
    static struct shell self;

    (void)argc;
    if (!shell_init(&self, argc, argv) || !shell_process(&self,
        self.should_set_interrupts) || !shell_signal_handle_pending(&self))
        do_fatal(&self);
    if (self.input_is_tty)
        shell_printf(&self, "exit\n");
    shell_exit_from_status(&self);
    return 0;
}
