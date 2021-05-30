/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines add
*/

#include "../proc.h"
#include "../parse_tree.h"
#include "../../shell.h"
#include "my/cpp-like/algorithm.h"
#include "my/assert.h"
#include "my/stdlib.h"

// Note: We try hard to avoid job indexes above 9 (like tcsh), which is why if
// we can't easily get that we'll search for the smallest unused job index
static void do_index(struct shell *self, struct shell_proc *proc)
{
    bool do_continue = false;

    if (self->proc_max_index < 9)
        proc->index = ++self->proc_max_index;
    else {
        for (int i = 1;; ++i) {
            do_continue = false;
            for (struct shell_proc *j = self->head_proc.next; j != NULL; j =
                j->next)
                if (j->index == i) {
                    do_continue = true;
                    break;
                }
            if (do_continue)
                continue;
            proc->index = i;
            self->proc_max_index = MY_MAX(self->proc_max_index, i);
        }
    }
}

static void do_current_job_null(struct shell *self, struct shell_proc *proc)
{
    self->current_job = proc;
    proc->job_leader_pid = proc->pid;
    proc->next_in_job_list = proc;
    proc->current_dir = self->current_dir;
    ++self->current_dir->ref_count;
    do_index(self, proc);
    if (self->current_job_in_table == NULL)
        self->current_job_in_table = proc;
    else if (self->previous_job_in_table == NULL)
        self->previous_job_in_table = proc;
}

static void do_current_job(struct shell *self, struct shell_proc *proc)
{
    struct shell_proc *i;

    if (self->current_job != NULL) {
        proc->current_dir = NULL;
        proc->index = self->current_job->index;
        proc->next_in_job_list = self->current_job;
        proc->job_leader_pid = self->current_job->pid;
        for (i = self->current_job; i->next_in_job_list != self->current_job;
            i = i->next_in_job_list);
        i->next_in_job_list = proc;
    } else
        do_current_job_null(self, proc);
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
