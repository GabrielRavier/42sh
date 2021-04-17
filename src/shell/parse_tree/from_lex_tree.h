/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares lex_tree_to_parse_tree
*/

#pragma once

#include "../parse_tree.h"
#include "../../shell.h"
#include "../../lexical_word_list.h"

enum {
    PARSER_FLAGS_OUTPUT = 0x1,
    PARSER_FLAGS_INPUT = 0x2,
};

struct shell_parse_tree *shell_parse_tree_from_lex_tree(struct shell *self,
    struct lexical_word_list *word_list_start,
    struct lexical_word_list *word_list_end, int flags);
