/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines add
*/

#include "../proc.h"
#include "../parse_tree.h"
#include "../../shell.h"
#include "my/assert.h"
#include "my/stdlib.h"

static void do_current_job(struct shell *self, struct shell_proc *proc)
{
    struct shell_proc *i;

    if (self->current_job) {
        proc->next_in_job_list = self->current_job;
        proc->job_leader_pid = self->current_job->pid;
        for (i = self->current_job; i->next_in_job_list != self->current_job;
            i = i->next_in_job_list)
            ;
        i->next_in_job_list = proc;
    } else {
        self->current_job = proc;
        proc->job_leader_pid = proc->pid;
        proc->next_in_job_list = proc;
        proc->current_dir = self->current_dir;
        ++self->current_dir->ref_count;
        if (self->current_job_in_table == NULL)
            self->current_job_in_table = proc;
        else if (self->previous_job_in_table == NULL)
            self->previous_job_in_table = proc;
    }
}

void shell_proc_add(struct shell *self, pid_t pid,
    struct shell_parse_tree *parse_tree)
{
    struct shell_proc *proc = my_xcalloc(1, sizeof(*proc));

    proc->pid = pid;
    proc->parent_id = self->pgrp;
    proc->flags = SHELL_PROC_FLAG_RUNNING | SHELL_PROC_FLAG_FOREGROUND;
    if (parse_tree->flags & PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT)
        proc->flags |= SHELL_PROC_FLAG_PIPE_OUTPUT;
    do_current_job(self, proc);
    proc->next = self->head_proc.next;
    self->head_proc.next = proc;
}
