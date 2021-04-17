/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines strlen
*/

#include "../shell_char.h"

size_t shell_char_strlen(const shell_char_t *str)
{
    size_t result = 0;

    while (*str++ != '\0')
        ++result;
    return result;
}
