/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines wait
*/

#include "../proc.h"
#include "../../shell.h"
#include "my/assert.h"
#include "my/stdlib.h"
#include <sys/wait.h>
#include <sys/types.h>

static void set_status_reason(struct shell *self, int status)
{
    if (WIFSTOPPED(status)) {
        self->current_proc.flags |= SHELL_PROC_FLAG_STOPPED;
        self->current_proc.reason = WSTOPSIG(status);
    } else {
        if (WIFSIGNALED(status)) {
            self->current_proc.flags |= WTERMSIG(status) == SIGINT ?
                SHELL_PROC_FLAG_INTERRUPTED : SHELL_PROC_FLAG_SIGNALED;
            if (WCOREDUMP(status))
                self->current_proc.flags |= SHELL_PROC_FLAG_DUMPED_CORE;
            self->current_proc.reason = WTERMSIG(status);
        } else {
            self->current_proc.reason = WEXITSTATUS(status);
            self->current_proc.flags |= (self->current_proc.reason != 0) ?
                SHELL_PROC_FLAG_ABNORMAL_EXIT : SHELL_PROC_FLAG_NORMAL_EXIT;
        }
    }
}

void shell_proc_wait_current(struct shell *self)
{
    int status;
    pid_t wait_result;

    MY_ASSERT(self->current_proc.pid != -1);
    do
        wait_result = wait(&status);
    while (wait_result != self->current_proc.pid);
    self->current_proc.flags &= ~(SHELL_PROC_FLAG_RUNNING |
        SHELL_PROC_FLAG_STOPPED);
    set_status_reason(self, status);
    if (self->current_proc.flags & (SHELL_PROC_FLAG_SIGNALED |
        SHELL_PROC_FLAG_STOPPED)) {
        MY_ASSERT(!(self->current_proc.flags & SHELL_PROC_FLAG_STOPPED));
        shell_proc_print(self, &self->current_proc,
            SHELL_PROC_PRINT_REASON_FILTERED);
    }
    self->last_command_exit_status = self->current_proc.reason |
        (self->current_proc.flags & SHELL_PROC_FLAG_SIGNALED ? 0x80 : 0);
    self->current_proc.pid = -1;
}
