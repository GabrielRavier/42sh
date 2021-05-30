/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines wait
*/

#include "../proc.h"
#include "../../shell.h"
#include "my/assert.h"
#include "my/stdlib.h"
#include <sys/wait.h>
#include <sys/types.h>

// This is where we get rid of dead processes
bool shell_proc_wait_current(struct shell *self)
{
    struct shell_proc *i = &self->head_proc;
    struct shell_proc *j = i->next;

    while (j != NULL) {
        if (j->pid == 0) {
            i->next = j->next;
            shell_proc_free(j);
            j = i;
        }
        i = j;
        j = i->next;
    }
    return shell_proc_wait(self, self->current_job);
}
