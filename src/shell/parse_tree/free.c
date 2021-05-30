/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines free
*/

#include "../parse_tree.h"
#include "my/stdlib.h"

static void free_command(struct shell_parse_tree *self)
{
    for (shell_char_t **argv = self->argv; *argv != NULL; ++argv)
        my_free(*argv);
    my_free(self->argv);
    my_free(self->str_left);
    my_free(self->str_right);
}

void shell_parse_tree_free(struct shell_parse_tree *self)
{
    if (self == NULL)
        return;
    switch (self->type) {
    case PARSE_TREE_TYPE_COMMAND:
        free_command(self);
        break;
    case PARSE_TREE_TYPE_LIST:
    case PARSE_TREE_TYPE_PIPE:
    case PARSE_TREE_TYPE_AND:
    case PARSE_TREE_TYPE_OR:
        shell_parse_tree_free(self->node_left);
        shell_parse_tree_free(self->node_right);
        break;
    case PARSE_TREE_TYPE_PARENS:
        shell_parse_tree_free(self->paren_subtree);
        my_free(self->str_left);
        my_free(self->str_right);
        break;
    }
    my_free(self);
}
