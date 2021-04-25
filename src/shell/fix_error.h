/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares fix_error
*/

#pragma once

#include "../shell.h"

/// This will unset child_io_fds_setup, exit if we're a child shell, reset the
/// state of the input and set the status to 1
void shell_fix_error(struct shell *self);
