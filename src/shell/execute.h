/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares execute
*/

#pragma once

#include "../shell.h"
#include "parse_tree.h"

typedef struct {
    struct shell *self;
    struct shell_parse_tree *parse_tree;
    int *pipe_in;
    int *pipe_out;
    pid_t want_tty;
} se_opts_t;

typedef bool (shell_execute_like_func_t)(se_opts_t *);

bool shell_execute(se_opts_t *o) MY_ATTR_WARN_UNUSED_RESULT;
