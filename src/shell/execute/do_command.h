/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares do_command
*/

#pragma once

#include "../../shell.h"
#include <stdbool.h>

bool shell_execute_do_command(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out)
    MY_ATTR_WARN_UNUSED_RESULT;
