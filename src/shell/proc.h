/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares proc
*/

#pragma once

#include <sys/types.h>

// SHELL_PROC_FLAG_SIGNALED is when the process was terminated by a signal,
// except if it was terminated by SIGINT, in which case
// SHELL_PROC_FLAG_INTERRUPTED is set
struct shell_proc {
    struct shell_proc *next;
    pid_t pid;
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
        SHELL_PROC_FLAG_ALL_STATUSES = SHELL_PROC_FLAG_RUNNING |
            SHELL_PROC_FLAG_STOPPED | SHELL_PROC_FLAG_NORMAL_EXIT |
            SHELL_PROC_FLAG_ABNORMAL_EXIT | SHELL_PROC_FLAG_SIGNALED |
            SHELL_PROC_FLAG_INTERRUPTED,
    } flags;
    unsigned char reason;
};

struct shell;
struct shell_parse_tree;

void shell_proc_add(struct shell *self, pid_t pid,
    struct shell_parse_tree *parse_tree);
void shell_proc_wait_current(struct shell *self);

enum {
    SHELL_PROC_PRINT_REASON_FILTERED = 1
};

void shell_proc_print(struct shell *self, struct shell_proc *proc, int flags);
