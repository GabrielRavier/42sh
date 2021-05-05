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
struct shell_parse_tree {
    enum {
        PARSE_TREE_NODE_TYPE_COMMAND,
        PARSE_TREE_NODE_TYPE_LIST,
        PARSE_TREE_NODE_TYPE_PIPE
    } type;
    enum {
        PARSE_TREE_NODE_FLAGS_APPEND = 0x1,
        PARSE_TREE_NODE_FLAGS_INPUT_HEREDOC = 0x2,
        PARSE_TREE_NODE_FLAGS_INTERRUPT_IMMUNE = 0x4,
        PARSE_TREE_NODE_FLAGS_PIPE_INPUT = 0x8,
        PARSE_TREE_NODE_FLAGS_PIPE_OUTPUT = 0x10,
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
};

void shell_parse_tree_free(struct shell_parse_tree *self);
