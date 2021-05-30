/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines internals for from_lex_tree_part3
*/

#pragma once

typedef struct {
    struct shell *self;
    struct lexical_word_list *word_list;
    struct lexical_word_list *word_list_end;
    int flags;
    struct lexical_word_list *i;
} dnl_opts_t;
