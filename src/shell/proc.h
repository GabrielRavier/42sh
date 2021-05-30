/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares proc
*/

#pragma once

#include "../dir.h"
#include <sys/types.h>

// SHELL_PROC_FLAG_SIGNALED is when the process was terminated by a signal,
// except if it was terminated by SIGINT, in which case
// SHELL_PROC_FLAG_INTERRUPTED is set
struct shell_proc {
    struct shell_proc *next;
    struct shell_proc *next_in_job_list;
    pid_t pid;
    pid_t parent_id;
    pid_t job_leader_pid;
    enum {
        SHELL_PROC_FLAG_RUNNING = 0x1,
        SHELL_PROC_FLAG_PIPE_OUTPUT = 0x2,
        SHELL_PROC_FLAG_SIGNALED = 0x4,
        SHELL_PROC_FLAG_ABNORMAL_EXIT = 0x8,
        SHELL_PROC_FLAG_NORMAL_EXIT = 0x10,
        SHELL_PROC_FLAG_FOREGROUND = 0x20,
        SHELL_PROC_FLAG_STOPPED = 0x40,
        SHELL_PROC_FLAG_INTERRUPTED = 0x80,
        SHELL_PROC_FLAG_DUMPED_CORE = 0x100,
        SHELL_PROC_FLAG_REPORTED = 0x200,
        SHELL_PROC_FLAG_ALL_STATUSES = SHELL_PROC_FLAG_RUNNING |
            SHELL_PROC_FLAG_STOPPED | SHELL_PROC_FLAG_NORMAL_EXIT |
            SHELL_PROC_FLAG_ABNORMAL_EXIT | SHELL_PROC_FLAG_SIGNALED |
            SHELL_PROC_FLAG_INTERRUPTED,
    } flags;
    unsigned char reason;
    struct dir *current_dir;
    int index;
};

struct shell;
struct shell_parse_tree;

void shell_proc_add(struct shell *self, pid_t pid,
    struct shell_parse_tree *parse_tree);
bool shell_proc_wait_current(struct shell *self) MY_ATTR_WARN_UNUSED_RESULT;
bool shell_proc_wait(struct shell *self, struct shell_proc *proc)
    MY_ATTR_WARN_UNUSED_RESULT;

/// This function makes it so that proc is not the current nor the previous job
/// (note: proc must be its job's leader)
void shell_proc_clear_current_previous(struct shell *self,
    struct shell_proc *proc);

/// This function finds the most recent job that is not proc. It prefers
/// stopped jobs
struct shell_proc *shell_proc_get_new_current_job(struct shell *self,
    struct shell_proc *proc);

enum {
    SHELL_PROC_PRINT_REASON_FILTERED = 0x1,
    SHELL_PROC_PRINT_SHELL_DIR_IF_DIFF = 0x2,
};

void shell_proc_print(struct shell *self, struct shell_proc *proc, int flags);
void shell_proc_flush(struct shell *self, struct shell_proc *proc);
void shell_proc_flush_all(struct shell *self);
bool shell_proc_any_stopped(struct shell *self, bool need_newline)
    MY_ATTR_WARN_UNUSED_RESULT;

// Executed when we're just done running a job, or when we're just about to
// begin doing so
void shell_proc_end_job(struct shell *self);
void shell_proc_free(struct shell_proc *self);
