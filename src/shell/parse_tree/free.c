/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines free
*/

#include "../parse_tree.h"
#include "my/stdlib.h"

void shell_parse_tree_free(struct shell_parse_tree *self)
{
    if (self == NULL)
        return;
    switch (self->type) {
    case PARSE_TREE_NODE_TYPE_COMMAND:
        for (shell_char_t **argv = self->argv; *argv != NULL; ++argv)
            my_free(*argv);
        my_free(self->argv);
        my_free(self->str_left);
        my_free(self->str_right);
        break;
    case PARSE_TREE_NODE_TYPE_LIST:
    case PARSE_TREE_NODE_TYPE_PIPE:
        shell_parse_tree_free(self->node_left);
        shell_parse_tree_free(self->node_right);
        break;
    }
    my_free(self);
}
