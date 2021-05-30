/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares cleanup_fds
*/

#pragma once

#include "../shell.h"

// This is called after we get an error, so as to cleanup anything we might have
// left open accidentally
void shell_cleanup_fds(struct shell *self);
