/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines jobs
*/

#include "../commands.h"
#include "../../set_error.h"

static const shell_char_t DASHL[] = {'-', 'l', '\0'};

static void do_loop(struct shell *self, int print_flags)
{
    for (int i = 1; i <= self->proc_max_index; ++i)
        for (struct shell_proc *j = self->head_proc.next; j != NULL;
            j = j->next)
            if (j->index == i && j->pid == j->job_leader_pid) {
                if (!(shell_proc_print(self, j, print_flags) &
                    (SH_PROC_FLAG_RUNNING | SH_PROC_FLAG_STOPPED)))
                    shell_proc_flush(self, j);
                break;
            }
}

void shell_builtin_jobs(struct shell *self, shell_char_t **argv)
{
    int print_flags = SHELL_PROC_PRINT_NUMBER | SHELL_PROC_PRINT_NAME |
        SHELL_PROC_PRINT_REASON | SHELL_PROC_PRINT_JOB_LIST;

    if (self->check_stop != 0)
        self->check_stop = 2;
    if (argv[1] != NULL) {
        if (argv[2] != NULL || shell_char_strcmp(argv[1], DASHL) != 0) {
            shell_set_error(self, SHELL_ERROR_JOBS_USAGE);
            return;
        }
        print_flags |= SHELL_PROC_PRINT_FANCY | SHELL_PROC_PRINT_JOB_LIST;
    }
    do_loop(self, print_flags);
}
