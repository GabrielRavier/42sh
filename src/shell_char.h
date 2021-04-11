/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares shell_char_t
*/

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t shell_char_t;

static const shell_char_t SHELL_CHAR_ERROR = 0xFFFFFFFF;
static const shell_char_t SHELL_CHAR_QUOTE = 0x80000000;

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
