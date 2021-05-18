/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_and_print_error
*/

#pragma once

#include "../shell.h"
#include "set_error.h"
#include "print_error.h"

void shell_set_and_print_error(struct shell *self, enum shell_error_type error,
    ...);
