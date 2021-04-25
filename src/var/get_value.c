/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines get_value
*/

#include "../var.h"

static const shell_char_t NUL_CHAR = '\0';

const shell_char_t *var_get_value(struct var *head, const shell_char_t *name)
{
    struct var *node;

    if (head == NULL || name == NULL)
        return &NUL_CHAR;
    node = var_get(head, name);
    return ((node == NULL || node->valv == NULL) ? &NUL_CHAR : node->valv[0]);
}
