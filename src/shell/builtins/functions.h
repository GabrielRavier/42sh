/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares builtin functions
*/

#pragma once

#include "../../shell.h"

int shell_builtin_env(struct shell *self);
int shell_builtin_setenv(struct shell *self);
int shell_builtin_unsetenv(struct shell *self);
int shell_builtin_cd(struct shell *self);
int shell_builtin_exit(struct shell *self);
