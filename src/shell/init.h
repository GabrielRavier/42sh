/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares init
*/

#pragma once

#include "../shell.h"
#include "my/features.h"

bool shell_init(struct shell *self, const char *argv0)
    MY_ATTR_WARN_UNUSED_RESULT;
void shell_init_fds(struct shell *self);
bool shell_init_home(struct shell *self, const shell_char_t **result)
    MY_ATTR_WARN_UNUSED_RESULT;
bool shell_init_dir(struct shell *self, const shell_char_t *home_val)
    MY_ATTR_WARN_UNUSED_RESULT;
void shell_init_program_name(struct shell *self, const char *argv0);
