/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares shell_state
*/

#pragma once

#include "shell/proc.h"
#include "lexical_word_list.h"
#include "shell_char.h"
#include <stdint.h>
#include <stdbool.h>

struct shell_lex_state {
    shell_char_t peek_character;
};

enum shell_error_type {
    SHELL_ERROR_NO_ERROR,
    SHELL_ERROR_MISSING_NAME_FOR_REDIRECTION,
    SHELL_ERROR_AMBIGUOUS_OUTPUT_REDIRECT,
    SHELL_ERROR_AMBIGUOUS_INPUT_REDIRECT,
    SHELL_ERROR_NULL_COMMAND,
    SHELL_ERROR_NO_MORE_PROCESSES,
    SHELL_ERROR_NO_HOME_DIRECTORY,
    SHELL_ERROR_TOO_MANY_ARGUMENTS,
    SHELL_ERROR_SYSTEM,
    SHELL_ERROR_CANT_CHANGE_TO_HOME_DIR,
    SHELL_ERROR_VAR_NAME_MUST_BEGIN_LETTER,
    SHELL_ERROR_VAR_NAME_MUST_CONTAIN_ALNUM,
    SHELL_ERROR_TOO_FEW_ARGUMENTS,
    SHELL_ERROR_CANT_MAKE_PIPE,
    SHELL_ERROR_LAST_ERROR,
};

// SAFE_FD is so that we don't touch the first 5 fds (we use 5 to be really
// safe, though it is also somewhat related to fd passthrough issues). This,
// along with the rest of these are mostly to facilitate work related to the
// standard fds
enum {
    SHELL_SAFE_FD = 5,
    SHELL_PREFERRED_INPUT_FD = 16,
    SHELL_PREFERRED_OUTPUT_FD = 17,
    SHELL_PREFERRED_ERROR_OUTPUT_FD = 18,
    SHELL_PREFERRED_OLD_STDIN_FD = 19,
};

// The input/output/error_output members are to seperate the fds for the shell
// from the ones used by standard operations, which often makes some stuff
// easier for us (avoids certain problems with /dev/std{in,out,err}, for
// example)
struct shell {
    int input_fd;
    int output_fd;
    int error_output_fd;
    int old_stdin_fd;
    int last_command_exit_status;
    bool input_is_tty;
    bool should_set_interrupts;
    bool child_io_fds_setup;
    void (*parent_sigint_handler)(int);
    shell_char_t peek_read;
    char *error;
    struct lexical_word_list current_lexical_word;
    struct shell_lex_state lex;
    struct shell_proc current_proc;
};
