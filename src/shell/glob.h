/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares glob
*/

#pragma once

#include "../shell.h"

// This determines what we do if a glob_str ends up with multiple words
enum {
    SHELL_GLOB_STR_FLAG_ERROR,
};

bool shell_glob_str(struct shell *self, const shell_char_t *str, int flags,
    shell_char_t **result);

bool shell_glob_do_tcsh(struct shell *self, const shell_char_t **strv,
    shell_char_t ***result);

// We don't handle stuff that would be handled by actual glob(3) calls yet, so we
// just have the tcsh-specific stuff for now
enum {
    SHELL_GLOB_FLAG_NONE = 0,
    SHELL_GLOB_FLAG_TCSH = 1,
};

int shell_glob_strv_get_flags(const shell_char_t **strv);
