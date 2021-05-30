/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares read_character
*/

#pragma once

#include "../shell.h"
#include "my/features.h"

// Reads a character from stdin. Exits if it fails.
bool shell_read_character(struct shell *self, bool want_eof,
    shell_char_t *result) MY_ATTR_WARN_UNUSED_RESULT;
