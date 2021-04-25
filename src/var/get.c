/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines get
*/

#include "../var.h"

struct var *var_get(struct var *head, const shell_char_t *name)
{
    int compare_result;

    for (head = head->left; head != NULL; head = (compare_result < 0) ?
        head->left : head->right) {
        compare_result = shell_char_strcmp(name, head->name);
        if (compare_result == 0)
            break;
    }
    return head;
}
