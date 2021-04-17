/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares shell_char_t
*/

#pragma once

#include "my/features.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint32_t shell_char_t;

static const shell_char_t SHELL_CHAR_ERROR = 0xFFFFFFFF;
static const shell_char_t SHELL_CHAR_QUOTE = 0x80000000;
static const shell_char_t SHELL_CHAR_NOT_QUOTE = 0x7FFFFFFF;

enum {
    SHELL_CHAR_TYPE_META = 0x1,
    SHELL_CHAR_TYPE_ESCAPE = 0x2,
};

static const unsigned char SHELL_CHAR_TYPE_MAP[0x100] = {
    ['\t'] = SHELL_CHAR_TYPE_META,
    ['\n'] = SHELL_CHAR_TYPE_META,
    [' '] = SHELL_CHAR_TYPE_META,
    [';'] = SHELL_CHAR_TYPE_META,
    ['<'] = SHELL_CHAR_TYPE_META,
    ['>'] = SHELL_CHAR_TYPE_META,
    ['\\'] = SHELL_CHAR_TYPE_ESCAPE,
    ['|'] = SHELL_CHAR_TYPE_META,
};

static inline bool shell_char_is_type(shell_char_t c, unsigned type)
{
    if ((c & SHELL_CHAR_QUOTE) || c >= 0x80)
        return false;
    return SHELL_CHAR_TYPE_MAP[c] & type;
}

shell_char_t *shell_char_xstrdup(const shell_char_t *str) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));
size_t shell_char_strlen(const shell_char_t *string) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_NONNULL((1)) MY_ATTR_PURE
    MY_ATTR_ACCESS((read_only, 1));
char *shell_char_cstrchr(const char *string, shell_char_t c)
    MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));
int shell_char_strcmp(const shell_char_t *string1,
    const shell_char_t *string2) MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_PURE MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((read_only, 1))
    MY_ATTR_ACCESS((read_only, 2));
int shell_char_cstrcmp_ignore_quote(const shell_char_t *string1,
    const char *string2) MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT
    MY_ATTR_PURE MY_ATTR_NONNULL((1, 2)) MY_ATTR_ACCESS((read_only, 1))
    MY_ATTR_ACCESS((read_only, 2));
char *shell_char_xstrdup_to_c(const shell_char_t *str) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));
char **shell_char_xdup_strv_to_c(shell_char_t *const *strv) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));
