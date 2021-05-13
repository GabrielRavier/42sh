/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares do_redirection
*/

#pragma once

#include "../../shell.h"

void shell_execute_do_redirection(struct shell *self,
    struct shell_parse_tree *parse_tree, int *pipe_in, int *pipe_out);
