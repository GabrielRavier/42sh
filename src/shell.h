/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares shell_state
*/

#pragma once

#include "lexical_word_list.h"
#include "shell_char.h"
#include <stdint.h>
#include <stdbool.h>

struct shell_lex_state {
    shell_char_t peek_character;
};

struct shell {
    int input_fd;
    int last_command_exit_status;
    bool is_interactive;
    shell_char_t peek_read;
    struct lexical_word_list current_lexical_word;
    struct shell_lex_state lex;
};
