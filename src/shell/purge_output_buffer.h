/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines purge_output_buffer
*/

#pragma once

#include "../shell.h"

static inline void shell_purge_output_buffer(struct shell *self)
{
    self->line_buffer_current_ptr = self->line_buffer;
}
