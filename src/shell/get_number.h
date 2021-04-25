/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines get_number
*/

#pragma once

#include "../shell_char.h"
#include "../shell.h"

bool shell_get_number(struct shell *self, const shell_char_t *str,
    long long *result);
