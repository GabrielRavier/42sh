/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines tree_balance
*/

#include "../var.h"
#include "tree_balance_part2.h"

static void already_right_heavy(struct var **start, struct var *parent,
    bool next_is_right)
{
    switch ((*start)->right->balance) {
    case 1:
        parent->links[next_is_right] = var_tree_balance_rotate_left(start);
        (*start)->left->balance = 0;
        (*start)->balance = 0;
        break;
    case 0:
        parent->links[next_is_right] = var_tree_balance_rotate_left(start);
        (*start)->left->balance = 1;
        (*start)->balance = -1;
        break;
    case -1:
        var_tree_balance_rotate_right(&(*start)->right);
        parent->links[next_is_right] = var_tree_balance_rotate_left(start);
        (*start)->left->balance = -1 + ((*start)->balance < 1);
        (*start)->right->balance = (*start)->balance > -1;
        (*start)->balance = 0;
        break;
    }
}

static void already_left_heavy(struct var **start, struct var *parent,
    bool next_is_right)
{
    switch ((*start)->left->balance) {
    case -1:
        parent->links[next_is_right] = var_tree_balance_rotate_right(start);
        (*start)->right->balance = 0;
        (*start)->balance = 0;
        break;
    case 0:
        parent->links[next_is_right] = var_tree_balance_rotate_right(start);
        (*start)->right->balance = -1;
        (*start)->balance = 1;
        break;
    case 1:
        var_tree_balance_rotate_left(&(*start)->left);
        parent->links[next_is_right] = var_tree_balance_rotate_right(start);
        (*start)->left->balance = -1 + ((*start)->balance < 1);
        (*start)->right->balance = ((*start)->balance > -1);
        (*start)->balance = 0;
        break;
    }
}

void var_tree_balance(struct var *start, bool is_from_right_child)
{
    struct var *parent;
    bool next_is_right;

    while (start->parent) {
        parent = start->parent;
        next_is_right = (parent->right == start);
        switch (is_from_right_child ? start->balance : -start->balance) {
        case -1:
        case 0:
            start->balance += is_from_right_child ? 1 : -1;
            break;
        case 1:
            (is_from_right_child ? &already_right_heavy : &already_left_heavy)
                (&start, parent, next_is_right);
        }
        if (start->balance == 0)
            break;
        start = parent;
        is_from_right_child = next_is_right;
    }
}
