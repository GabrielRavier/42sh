/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines parse_tree
*/

#pragma once

#include "../shell_char.h"

/// node_left and node_right are set if the node is a pipe
/// node_left and node_right *may* be set if the node is a list
/// str_left and str_right *may* be set if the node is a command
/// argv is only relevant if the node is a command
/// PARSE_TREE_FLAG_NO_FORK is set when the command is the last in a (), so as
/// to economize on the amount of fork calls
struct shell_parse_tree {
    enum {
        PARSE_TREE_TYPE_COMMAND,
        PARSE_TREE_TYPE_SMALLEST = PARSE_TREE_TYPE_COMMAND,
        PARSE_TREE_TYPE_LIST,
        PARSE_TREE_TYPE_PIPE,
        PARSE_TREE_TYPE_OR,
        PARSE_TREE_TYPE_AND,
        PARSE_TREE_TYPE_PARENS,
        PARSE_TREE_TYPE_BIGGEST = PARSE_TREE_TYPE_PARENS,
    } type;
    enum {
        PARSE_TREE_FLAG_APPEND = 0x1,
        PARSE_TREE_FLAG_INPUT_HEREDOC = 0x2,
        PARSE_TREE_FLAG_INTERRUPT_IMMUNE = 0x4,
        PARSE_TREE_FLAG_PIPE_INPUT = 0x8,
        PARSE_TREE_FLAG_PIPE_OUTPUT = 0x10,
        PARSE_TREE_FLAG_AMPERSAND = 0x20,
        PARSE_TREE_FLAG_NO_FORK = 0x40,
    } flags;
    union {
        struct shell_parse_tree *node_left;
        shell_char_t *str_left;
    };
    union {
        struct shell_parse_tree *node_right;
        shell_char_t *str_right;
    };
    shell_char_t **argv;
    struct shell_parse_tree *paren_subtree;
};

struct shell;
struct lexical_word_list;

struct shell_parse_tree *shell_parse_tree_from_lex_tree(struct shell *self,
    struct lexical_word_list *word_list_start,
    struct lexical_word_list *word_list_end, int flags);
void shell_parse_tree_free(struct shell_parse_tree *self);
