/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares init
*/

#pragma once

#include "../shell.h"

void shell_init(struct shell *self, const char *argv0);
void shell_init_fds(struct shell *self);
const shell_char_t *shell_init_home(struct shell *self);
void shell_init_dir(struct shell *self, const shell_char_t *home_val);
void shell_init_program_name(struct shell *self, const char *argv0);
