/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares builtin
*/

#pragma once

#include "parse_tree.h"
#include "../shell.h"

struct shell_builtin {
    const char *name;
    void (*func)(struct shell *, shell_char_t **);
    size_t min_arguments;
    size_t max_arguments;
};

struct shell_builtin *shell_builtin_find(struct shell_parse_tree *parse_tree);
void shell_builtin_run(struct shell *self, const struct shell_builtin *builtin,
    struct shell_parse_tree *parse_tree);
