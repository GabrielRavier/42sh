/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares fork
*/

#pragma once

#include "../shell.h"
#include "parse_tree.h"
#include <sys/types.h>

bool shell_fork(struct shell *self, struct shell_parse_tree *parse_tree,
    pid_t want_tty, pid_t *result) MY_ATTR_WARN_UNUSED_RESULT;
