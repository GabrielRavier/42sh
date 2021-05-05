/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines dir
*/

#pragma once

#include "shell_char.h"

// This is implemented as a linked list with a loop. It includes a reference
// count, for implementing process stuff in the future (when we want to print
// the cwd of a process)
struct dir {
    struct dir *next;
    struct dir *prev;
    shell_char_t *name;
    size_t ref_count;
};

void dir_free(struct dir *self);
