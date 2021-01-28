/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines read_character
*/

#include "read_character.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int read_character(void)
{
    char result;

    if (read(STDIN_FILENO, &result, sizeof(result)) != sizeof(result))
        exit(0);
    return (result);
}
