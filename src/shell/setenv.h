/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares setenv
*/

#pragma once

#include "../shell.h"

// Calls setenv with the given arguments (converted to C strings, ofc)
void shell_setenv(const shell_char_t *name, const shell_char_t *value);
