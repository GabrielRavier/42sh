/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares getpwnam
*/

#pragma once

#include "my/features.h"
#include <pwd.h>

struct passwd *shell_getpwnam(const char *name) MY_ATTR_WARN_UNUSED_RESULT;
