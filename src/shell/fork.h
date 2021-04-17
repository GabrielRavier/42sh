/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares fork
*/

#pragma once

#include "../shell.h"
#include "parse_tree.h"
#include <sys/types.h>

pid_t shell_fork(struct shell *self, struct shell_parse_tree *parse_tree);
