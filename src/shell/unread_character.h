/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines unread_character
*/

#pragma once

#include "../shell.h"

static inline void shell_unread_character(struct shell *self, char character)
{
    self->peek_read = character;
}
