/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares read_character
*/

#pragma once

#include "../shell.h"

// Reads a character from stdin. Exits if it fails.
shell_char_t shell_read_character(struct shell *self, bool want_eof);
