/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares glob
*/

#pragma once

#include "../shell.h"
#include "my/features.h"

// This determines what we do if a glob_str ends up with multiple words
enum {
    SHELL_GLOB_STR_FLAG_ERROR,
    SHELL_GLOB_STR_FLAG_APPEND,
};

bool shell_glob_str(struct shell *self, const shell_char_t *str, int flags,
    shell_char_t **result) MY_ATTR_WARN_UNUSED_RESULT;

bool shell_glob_do_tc_sh(struct shell *self, const shell_char_t **strv,
    shell_char_t ***result) MY_ATTR_WARN_UNUSED_RESULT;

// We don't handle stuff that would be handled by actual glob(3) calls yet, so
// we just have the tcsh-specific stuff for now
enum {
    SHELL_GLOB_FLAG_NONE = 0,
    SHELL_GLOB_FLAG_TCSH = 1,
};

int shell_glob_strv_get_flags(const shell_char_t **strv)
    MY_ATTR_WARN_UNUSED_RESULT;

MY_ATTR_WARN_UNUSED_RESULT static inline int shell_glob_strv_get_flags_ncsnt(
    shell_char_t **strv)
{
    return shell_glob_strv_get_flags((const shell_char_t **)strv);
}

bool shell_glob_strv_all(struct shell *self,
    const shell_char_t **strv, int flags, shell_char_t ***result)
    MY_ATTR_WARN_UNUSED_RESULT;

MY_ATTR_WARN_UNUSED_RESULT static inline bool shell_glob_strv_all_ncsnt(
    struct shell *self, shell_char_t **strv, int flags,
    shell_char_t ***result)
{
    return shell_glob_strv_all(self, (const shell_char_t **)strv, flags,
        result);
}
