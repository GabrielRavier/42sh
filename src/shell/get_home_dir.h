/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares get_home_dir
*/

#pragma once

#include "../shell.h"
#include "../shell_char.h"
#include "my/features.h"

shell_char_t *shell_get_home_dir(struct shell *self,
    const shell_char_t *username) MY_ATTR_WARN_UNUSED_RESULT;
