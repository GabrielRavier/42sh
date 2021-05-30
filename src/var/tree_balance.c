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

static void do_switch(struct var *start, bool do_right_or_left,
    struct var *parent, bool next_is_right)
{
    switch (do_right_or_left ? start->balance : -start->balance) {
    case -1:
    case 0:
        start->balance += do_right_or_left ? 1 : -1;
        break;
    case 1:
        (do_right_or_left ? &already_right_heavy : &already_left_heavy)(&start,
            parent, next_is_right);
    }
}

// Note: When we're inserting, we terminate when start is balanced, but if we're
// from delete, it's the exact opposite (we terminate when start is unbalanced)
void var_tree_balance(struct var *start, bool is_from_right_child,
    bool is_from_delete)
{
    struct var *parent;
    bool next_is_right;

    while (start->parent) {
        parent = start->parent;
        next_is_right = (parent->right == start);
        do_switch(start, is_from_right_child != is_from_delete, parent,
            next_is_right);
        if ((start->balance == 0) != is_from_delete)
            break;
        start = parent;
        is_from_right_child = next_is_right;
    }
}
