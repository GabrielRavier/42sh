/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares signal-related stuff
*/

#pragma once

#include "../shell.h"
#include <stdbool.h>

extern struct shell_signal_globals {
    _Atomic(bool) sigint_pending;
    _Atomic(bool) sigchld_pending;
} g_shell_signal;

void shell_signal_int_handler(int signal);
void shell_signal_chld_handler(int signal);
bool shell_signal_enable_sigint(struct shell *self, int *old_disable_sigint)
    MY_ATTR_WARN_UNUSED_RESULT;
bool shell_signal_decr_disable(struct shell *self, int *disable_sig)
    MY_ATTR_WARN_UNUSED_RESULT;
void shell_signal_set_interrupting_handler(int signal, void (*function)(int));
bool shell_signal_handle_pending(struct shell *self) MY_ATTR_WARN_UNUSED_RESULT;

bool shell_signal_process_chld(struct shell *self) MY_ATTR_WARN_UNUSED_RESULT;

// Note: will always set error, so the caller should return false
bool shell_signal_process_int(struct shell *self, bool do_newline)
    MY_ATTR_WARN_UNUSED_RESULT;
