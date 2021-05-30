/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines commands
*/

#pragma once

#include "../builtin.h"

void shell_builtin_cd(struct shell *self, shell_char_t **argv);
void shell_builtin_env(struct shell *self, shell_char_t **argv);
void shell_builtin_exit(struct shell *self, shell_char_t **argv);
void shell_builtin_jobs(struct shell *self, shell_char_t **argv);
void shell_builtin_printenv(struct shell *self, shell_char_t **argv);
void shell_builtin_setenv(struct shell *self, shell_char_t **argv);
void shell_builtin_unsetenv(struct shell *self, shell_char_t **argv);
void shell_builtin_wait(struct shell *self, shell_char_t **argv);
