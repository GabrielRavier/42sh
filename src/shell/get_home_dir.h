/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares get_home_dir
*/

#pragma once

#include "../shell.h"
#include "../shell_char.h"

shell_char_t *shell_get_home_dir(struct shell *self,
    const shell_char_t *username);
