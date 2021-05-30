/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares from_lex_tree_part4
*/

#pragma once

#include "../../shell.h"

struct shell_parse_tree *shell_parse_tree_from_lex_tree_part4(
    struct shell *self, struct lexical_word_list *word_list,
    struct lexical_word_list *word_list_end, int flags);
