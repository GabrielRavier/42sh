/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines unset
*/

#include "../var.h"
#include "my/stdlib.h"

// We start by freeing the memory associated with the variable since that's the
// simplest to do and will avoid complications
// When there's a missing child, it's simple: move the other into var.
// Otherwise, we find the predecessor of var, which will not have a right child,
// copy it into var and move its left child to it
// We then move the found child into where var is, rebalance the parent and free
// var
void var_unset(struct var *var)
{
    struct var *child;
    bool is_right;

    shell_char_strv_free(var->valv);
    my_free(var->name);
    if (var->right == NULL)
        child = var->left;
    else if (var->left == NULL)
        child = var->right;
    else {
        for (child = var->left; child->right != NULL; child = child->right);
        var->name = child->name;
        var->flags = child->flags;
        var->valv = child->valv;
        var = child;
        child = var->left;
    }
    is_right = var->parent->right == var;
    var->parent->links[is_right] = child;
    if (child != NULL)
        child->parent = var->parent;
    var_tree_balance(var->parent, is_right, true);
    my_free(var);
}
