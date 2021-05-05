/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines unread_character
*/

#pragma once

#include "../shell.h"

static inline void shell_unread_character(struct shell *self, char character)
{
    self->peek_read = character;
}
