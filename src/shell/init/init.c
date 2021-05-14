/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines init
*/

#include "../init.h"
#include "../exit.h"
#include "my/fcntl.h"
#include "my/unistd.h"
#include "my/string.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

// If someone has fun calling us with fd 0/1/2 closed, we might have problems,
// so guarantee them being open
static void guarantee_012_open(struct shell *self)
{
    int fd;

    do {
        fd = my_open("/dev/null", O_RDONLY);
        if (fd == -1) {
            fd = my_open("/", O_RDONLY);
            if (fd == -1)
                shell_exit(self, 1);
        }
    } while (fd < 3);
    my_close(fd);
}

bool shell_init(struct shell *self, const char *argv0)
{
    const shell_char_t *home_val;

    my_memset(self, 0, sizeof(*self));
    self->line_buffer_current_ptr = self->line_buffer;
    guarantee_012_open(self);
    shell_init_program_name(self, argv0);
    shell_init_fds(self);
    self->input_is_tty = isatty(self->input_fd);
    if (!shell_init_home(self, &home_val) || !shell_init_dir(self, home_val))
        return false;
    sigaction(SIGINT, NULL, &self->parent_sigint_action);
    if ((self->input_is_tty && isatty(self->output_fd)) ||
        self->parent_sigint_action.sa_handler == SIG_DFL)
        self->should_set_interrupts = true;
    self->pgrp = my_getpgrp();
    lexical_word_list_init(&self->current_lexical_word);
    return true;
}
