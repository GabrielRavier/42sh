/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares execute
*/

#pragma once

#include "../shell.h"
#include "parse_tree.h"

void shell_execute(struct shell *self, struct shell_parse_tree *parse_tree,
    int *pipe_in, int *pipe_out);
