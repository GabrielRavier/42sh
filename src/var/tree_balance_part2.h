/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines part 2 of tree_balance
*/

#pragma once

#include "../var.h"

// This does a single left rotation on start
static inline struct var *var_tree_balance_rotate_left(struct var **start)
{
    struct var *tmp = (*start)->right;

    tmp->parent = (*start)->parent;
    (*start)->right = tmp->left;
    if (tmp->left != NULL)
        tmp->left->parent = (*start);
    tmp->left = (*start);
    tmp->left->parent = tmp;
    *start = tmp;
    return tmp;
}

// This does a single right rotation on start
static inline struct var *var_tree_balance_rotate_right(struct var **start)
{
    struct var *tmp = (*start)->left;

    tmp->parent = (*start)->parent;
    (*start)->left = tmp->right;
    if (tmp->right != NULL)
        tmp->right->parent = (*start);
    tmp->right = (*start);
    tmp->right->parent = tmp;
    *start = tmp;
    return tmp;
}
