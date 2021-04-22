/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines mkstemp_openbsd_startup
*/

#pragma once

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <unistd.h>
#include <sys/mman.h>
#include <limits.h>

static inline void mkstemp_openbsd_startup(char cwd[PATH_MAX + 1], size_t *cwd_len, long *page_size, char **p)
{
    cr_assert_eq(chdir("/tmp"), 0);
    cr_assert_neq(getcwd(cwd, PATH_MAX - 1), NULL);

    *cwd_len = my_strlen(cwd);
    cwd[(*cwd_len)++] = '/';
    cwd[*cwd_len] = '\0';

    *page_size = sysconf(_SC_PAGESIZE);
    *p = mmap(NULL, *page_size * 3, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    cr_assert_neq(*p, MAP_FAILED);
    cr_assert_eq(mprotect(*p, *page_size, PROT_NONE), 0);
    cr_assert_eq(mprotect(*p + *page_size * 2, *page_size, PROT_NONE), 0);
    *p += *page_size;
}
