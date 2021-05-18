/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares shell_char_t
*/

#pragma once

#include "my/features.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint32_t shell_char_t;

#define SHELL_CHAR_ERROR ((uint32_t)0xFFFFFFFF)
static const shell_char_t SHELL_CHAR_QUOTED = 0x80000000;
static const shell_char_t SHELL_CHAR_NOT_QUOTED = 0x7FFFFFFF;

enum {
    SHELL_CHAR_TYPE_META = 0x1,
    SHELL_CHAR_TYPE_ESCAPE = 0x2,
    SHELL_CHAR_TYPE_QUOTE = 0x4,
    SHELL_CHAR_TYPE_SPACE = 0x8,
    SHELL_CHAR_TYPE_NEWLINE = 0x10,
    SHELL_CHAR_TYPE_ALL_QUOTES = SHELL_CHAR_TYPE_ESCAPE | SHELL_CHAR_TYPE_QUOTE,
};

static const unsigned char SHELL_CHAR_TYPE_MAP[0x80] = {
    ['\t'] = SHELL_CHAR_TYPE_META | SHELL_CHAR_TYPE_SPACE,
    ['\n'] = SHELL_CHAR_TYPE_META | SHELL_CHAR_TYPE_NEWLINE,
    [' '] = SHELL_CHAR_TYPE_META | SHELL_CHAR_TYPE_SPACE,
    [';'] = SHELL_CHAR_TYPE_META,
    ['<'] = SHELL_CHAR_TYPE_META,
    ['>'] = SHELL_CHAR_TYPE_META,
    ['\\'] = SHELL_CHAR_TYPE_ESCAPE,
    ['|'] = SHELL_CHAR_TYPE_META,
    ['&'] = SHELL_CHAR_TYPE_META,
    ['"'] = SHELL_CHAR_TYPE_QUOTE,
    ['\''] = SHELL_CHAR_TYPE_QUOTE,
};

MY_ATTR_WARN_UNUSED_RESULT static inline bool shell_char_is_type(shell_char_t c,
    unsigned type)
{
    if ((c & SHELL_CHAR_QUOTED) || c >= 0x80)
        return false;
    return SHELL_CHAR_TYPE_MAP[c] & type;
}

shell_char_t *shell_char_xstrdup(const shell_char_t *str) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));
shell_char_t *shell_char_xstrndup(const shell_char_t *str, size_t len)
    MY_ATTR_NOTHROW MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC
    MY_ATTR_NONNULL((1)) MY_ATTR_ACCESS((read_only, 1));
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
shell_char_t *shell_char_xstrdup_from_c(const char *str) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));

/// The result of this function is only valid until the next call to it
char *shell_char_static_xstrdup_to_c(const shell_char_t *str) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));

shell_char_t *shell_char_getcwd_malloced(void) MY_ATTR_WARN_UNUSED_RESULT;
shell_char_t *shell_char_str_quote(shell_char_t *str);

char **shell_char_xdup_strv_to_c(shell_char_t *const *strv) MY_ATTR_NOTHROW
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_MALLOC MY_ATTR_NONNULL((1))
    MY_ATTR_ACCESS((read_only, 1));
void shell_char_strv_free(shell_char_t **strv);
void shell_char_strv_unquote(shell_char_t **strv);
shell_char_t *shell_char_str_unquote(shell_char_t *str);
shell_char_t *shell_char_alloc_concat(const shell_char_t *left,
    const shell_char_t *right) MY_ATTR_WARN_UNUSED_RESULT;
shell_char_t **shell_char_strv_xdup(const shell_char_t **strv)
    MY_ATTR_WARN_UNUSED_RESULT;
size_t shell_char_strv_len(const shell_char_t **strv)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE;

// Note: The pointers from left and right are directly copied, the strings
// inside aren't duplicated or anything like that
shell_char_t **shell_char_strv_alloc_concat(shell_char_t **left,
    shell_char_t **right) MY_ATTR_WARN_UNUSED_RESULT;

shell_char_t **shell_char_strv_cpy(shell_char_t **dest, shell_char_t **src);
shell_char_t **shell_char_strv_cat(shell_char_t **dest, shell_char_t **src);
const shell_char_t **shell_char_strv_end(const shell_char_t **strv)
    MY_ATTR_WARN_UNUSED_RESULT;

MY_ATTR_WARN_UNUSED_RESULT static inline shell_char_t **
    shell_char_strv_xdup_ncnst(shell_char_t **strv)
{
    return shell_char_strv_xdup((const shell_char_t **)strv);
}

MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_PURE static inline size_t
    shell_char_strv_len_ncnst(shell_char_t **strv)
{
    return shell_char_strv_len((const shell_char_t **)strv);
}

MY_ATTR_WARN_UNUSED_RESULT static inline shell_char_t **
    shell_char_strv_end_ncnst(shell_char_t **strv)
{
    return (shell_char_t **)shell_char_strv_end((const shell_char_t **)strv);
}

// Little utility function for C strings that is just defined in terms of
// shell_char_strv_free since we can get away with it pretty easily
static inline void char_strv_free(char **strv)
{
    shell_char_strv_free((shell_char_t **)strv);
}

static inline void shell_char_strv_free_cnst(const shell_char_t **strv)
{
    shell_char_strv_free((shell_char_t **)strv);
}
