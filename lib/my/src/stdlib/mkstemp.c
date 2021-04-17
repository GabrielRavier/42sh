/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines mkstemp
*/

#include "my/stdlib.h"

int my_mkstemp(char *template)
{
    return my_mkstemps(template, 0);
}
