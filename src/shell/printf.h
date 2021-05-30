/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares printf
*/

#pragma once

#include "../shell.h"

#ifdef ENABLE_DEBUG_PRINTFS
    #define SHELL_DEBUG_PRINTF shell_printf
#else
    #define SHELL_DEBUG_PRINTF(...)
#endif

void shell_printf(struct shell *self, const char *format, ...) MY_ATTR_FORMAT(
    printf, 2, 3);
