/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines var
*/

#pragma once

#include "my/features.h"
#include "shell_char.h"

/// We store variables in an AVL tree
/// varv is an array of words which represents the value
struct var {
    shell_char_t **valv;
    shell_char_t *name;
    union {
        struct var *links[3];
        struct {
            struct var *left;
            struct var *right;
            struct var *parent;
        };
    };
    int balance;
    enum {
        VAR_FLAG_READ_WRITE = 0x1,
        VAR_FLAG_NO_GLOB = 0x2,
    } flags;
};

struct var *var_get(struct var *head, const shell_char_t *name)
    MY_ATTR_WARN_UNUSED_RESULT;
const shell_char_t *var_get_value(struct var *head, const shell_char_t *name)
    MY_ATTR_WARN_UNUSED_RESULT;
void var_tree_balance(struct var *start, bool is_from_right_child);
