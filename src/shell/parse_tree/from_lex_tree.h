/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares lex_tree_to_parse_tree internals
*/

#pragma once

enum {
    PARSER_FLAGS_OUTPUT = 0x1,
    PARSER_FLAGS_INPUT = 0x2,
    PARSER_FLAGS_PARENS = 0x4,
};

#define PARSER_SWITCH_PARENS_CASES(name) \
    case '(': \
        ++name; \
        continue; \
    case ')': \
        --name; \
        continue;
