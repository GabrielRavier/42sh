/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares shell_state
*/

#pragma once

#include <stdbool.h>

enum {
    LINE_STATE_ARGUMENTS_SIZE = 500,
    LINE_STATE_LINE_SIZE = 10000
};

struct my_string;

struct shell {
    char peek_character;
    char line[LINE_STATE_LINE_SIZE];
    char *arguments[LINE_STATE_ARGUMENTS_SIZE];
    char *line_ptr;
    char *end_line_ptr;
    char **arguments_ptr;
    char **end_arguments_ptr;
    bool has_errored;
    int last_command_exit_status;
    bool is_interactive;
};
