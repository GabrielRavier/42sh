/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines toupper
*/

#include "my/ctype.h"

int my_toupper(int c)
{
    return my_islower(c) ? (c - ('a' - 'A')) : c;
}
