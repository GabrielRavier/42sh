/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares tty-related functions
*/

#pragma once

#include "../shell.h"
#include "my/features.h"
#include <sys/types.h>
#include <stdbool.h>

bool shell_tty_grab_pgrp(int fd, pid_t wanted_pgrp) MY_ATTR_WARN_UNUSED_RESULT;
void shell_tty_ungrab(struct shell *self);
