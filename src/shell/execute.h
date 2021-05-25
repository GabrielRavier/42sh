/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares execute
*/

#pragma once

#include "../shell.h"
#include "parse_tree.h"

typedef bool (shell_execute_like_func_t)(struct shell *,
    struct shell_parse_tree *, int *, int *);

bool shell_execute(struct shell *self, struct shell_parse_tree *parse_tree,
    int *pipe_in, int *pipe_out) MY_ATTR_WARN_UNUSED_RESULT;
