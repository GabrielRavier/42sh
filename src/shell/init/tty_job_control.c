/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines tty_job_control
*/

#include "../init.h"
#include "../tty.h"
#include "../printf.h"
#include "../../fd.h"
#include "my/cpp-like/iterator.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static int get_tty_fd(struct shell *self)
{
    int fds[] = {self->error_output_fd, self->output_fd, self->old_stdin_fd};

    for (size_t i = 0; i < MY_ARRAY_SIZE(fds); ++i)
        if (isatty(fds[i]))
            return fds[i];
    return -1;
}

static void print_tty_error(struct shell *self, const char *prefix)
{
    shell_printf(self, "%s Warning: no access to tty (%s).\n"
        "Thus no job control in this shell.\n", prefix, strerror(errno));
}

static bool do_after_grab(struct shell *self, int fd)
{
    self->original_pgrp = self->pgrp;
    self->pgrp = getpid();
    self->terminal_pgrp = self->pgrp;
    if (tcsetpgrp(fd, self->pgrp) == -1) {
        if (setpgid(0, self->pgrp) == -1) {
            print_tty_error(self, "setpgid:");
            return false;
        }
        if (tcsetpgrp(fd, self->pgrp) == -1) {
            print_tty_error(self, "tcsetpgrp:");
            return false;
        }
    } else if (self->pgrp != getpgrp() && setpgid(0, self->pgrp) == -1) {
        print_tty_error(self, "setpgid:");
        return false;
    }
    fcntl(fd_copy(fd, SHELL_TTY_FD), F_SETFD, FD_CLOEXEC);
    return true;
}

void shell_init_tty_job_control(struct shell *self)
{
    int fd = get_tty_fd(self);

    if (fd != 1 && shell_tty_grab_pgrp(fd, self->pgrp) && !do_after_grab(self,
        fd))
        return;
    if (self->terminal_pgrp == -1)
        print_tty_error(self, "");
}
