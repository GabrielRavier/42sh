/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines set_error
*/

#pragma once

#include "../shell.h"

void shell_set_error(struct shell *self, enum shell_error_type error, ...);
