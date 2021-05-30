/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines init
*/

#include "../init.h"
#include "../open.h"
#include "../close.h"
#include "../cleanup_fds.h"
#include "../signal.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static const shell_char_t EDIT[] = {'e', 'd', 'i', 't', '\0'};

// If someone has fun starting us with fd 0/1/2 closed, we might have problems,
// so guarantee them being open
static void guarantee_012_open(void)
{
    int fd;

    do {
        fd = shell_open("/dev/null", O_RDONLY);
        if (fd == -1) {
            fd = shell_open("/", O_RDONLY);
            if (fd == -1)
                exit(1);
        }
    } while (fd < 3);
    shell_close(fd);
}

// The shell_cleanup_fds call is to make sure we don't inherit random fds we
// don't want
static void part2(struct shell *self)
{
    sigaction(SIGINT, NULL, &self->parent_sigint_action);
    sigaction(SIGINT, NULL, &self->parent_sigterm_action);
    shell_cleanup_fds(self);
    self->input_is_tty = isatty(self->input_fd);
    self->output_is_tty = isatty(self->output_fd);
    if (self->input_is_tty && self->output_is_tty)
        self->should_set_interrupts = true;
    self->pgrp = getpgrp();
    self->original_pgrp = -1;
    self->terminal_pgrp = -1;
    if (self->should_set_interrupts) {
        shell_init_interactive_interrupts(self);
        shell_init_tty_job_control(self);
    }
    if (self->parent_sigint_action.sa_handler == SIG_DFL)
        self->should_set_interrupts = true;
    shell_signal_set_interrupting_handler(SIGCHLD, shell_signal_chld_handler);
}

// If we're an interactive shell, we start fiddling with the signals
bool shell_init(struct shell *self, const char *argv0)
{
    const shell_char_t *home_val;

    *self = (struct shell){0};
    self->line_buffer_current_ptr = self->line_buffer;
    lexical_word_list_init(&self->current_lexical_word);
    guarantee_012_open();
    shell_init_program_name(self, argv0);
    shell_init_fds(self);
    self->last_command_exit_status = 0;
    if (!shell_init_home(self, &home_val) || !shell_init_dir(self, home_val) ||
        !shell_init_term(self) || !shell_init_path(self))
        return false;
    part2(self);
    return true;
}
