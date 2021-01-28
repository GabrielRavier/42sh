/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines init
*/

#include "init.h"
#include "my/my_string.h"

void shell_init(struct shell *self)
{
    *self = (struct shell){0};
}
