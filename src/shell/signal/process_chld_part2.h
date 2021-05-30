/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of process_chld
*/

#pragma once

#include "../../shell.h"
#include "../printf.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

static inline void do_raw_waitpid(struct shell *self, pid_t *pid, int *status)
{
    SHELL_DEBUG_PRINTF(self, "Doing waitpid...\n");
    errno = 0;
    *pid = waitpid(-1, status, (self->should_set_interrupts &&
        self->input_is_tty) ? WNOHANG | WUNTRACED : WNOHANG);
    SHELL_DEBUG_PRINTF(self, "As parent %jd, got pid %jd, status %x, "
        "WTERMSIG %x, WEXITSTATUS %x\n", (intmax_t)getpid(), (intmax_t)*pid,
        *status, WTERMSIG(*status), WEXITSTATUS(*status));
}
