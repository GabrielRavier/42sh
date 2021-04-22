/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines mktemp_netbsd_check_mode
*/

#pragma once

#include "../tests_header.h"
#include "my/stdlib.h"
#include <sys/stat.h>
#include <stdbool.h>

static inline void mktemp_netbsd_check_mode(const struct stat *stat_buffer, int mode, bool is_dir)
{
    cr_assert_neq(is_dir ? S_ISDIR(stat_buffer->st_mode) : S_ISREG(stat_buffer->st_mode), 0);
    cr_assert_neq(stat_buffer->st_mode & mode, 0);
}
