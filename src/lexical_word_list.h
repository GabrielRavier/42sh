/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares lexical_word_list
*/

#pragma once

#include "shell_char.h"

// The lexer makes input lines into circular double linked lists of words
struct lexical_word_list {
    struct lexical_word_list *next;
    struct lexical_word_list *prev;
    shell_char_t *word;
};

void lexical_word_list_init(struct lexical_word_list *self);
void lexical_word_list_free(struct lexical_word_list *self);
