/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests mkstemps
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "mktemp_netbsd_check_mode.h"
#include "mkstemp_openbsd_startup.h"
#include "mkstemp_openbsd_check.h"
#include "my/unistd.h"
#include "my/sys/stat.h"
#include "my/string.h"

Test(my_mkstemps, netbsd_basic)
{
    char template[] = "/tmp/mktemp.XXXyyy";
    const char *suffix = my_strchr(template, 'y');
    int fd = my_mkstemps(template, 3);
    cr_assert_neq(fd, -1);

    cr_assert_eq(my_strncmp(template, "/tmp/mktemp.", 12), 0);
    cr_assert_eq(my_strcmp(suffix, "yyy"), 0);
    cr_assert_eq(my_write(fd, "X", 1), 1);

    struct stat stat_buffer = {0};
    cr_assert_eq(my_fstat(fd, &stat_buffer), 0);
    mktemp_netbsd_check_mode(&stat_buffer, 0600, false);
    cr_assert_eq(my_close(fd), 0);
    cr_assert_eq(my_unlink(template), 0);
}

static void openbsd_try(char *path, const char *prefix, size_t x_len, const char *suffix)
{
    size_t prefix_len = my_strlen(prefix);
    size_t suffix_len = my_strlen(suffix);

    for (size_t i = 0; i < 100; ++i) {
        my_memcpy(path, prefix, prefix_len);
        my_memset(path + prefix_len, 'X', x_len);
        my_memcpy(path + prefix_len + x_len, suffix, suffix_len + 1);
        if (mkstemp_openbsd_check(my_mkstemps(path, suffix_len), path, prefix, prefix_len, suffix, suffix_len, x_len))
            return;
    }
    cr_assert(false && "Failed to successfully pass checks after 100 tries");
}

Test(my_mkstemps, openbsd)
{
    char cwd[PATH_MAX + 1];
    size_t cwd_len;
    long page_size;
    char *p;
    mkstemp_openbsd_startup(cwd, &cwd_len, &page_size, &p);

    static const char *const SUFFIX = ".suff";
    static const size_t SUFFIX_LEN = 5;
    for (size_t i = 11; i-- != 0;) {
        /* try first at the start of a page, no prefix */
        openbsd_try(p, "", i, "");
        /* now at the end of the page, no prefix */
        openbsd_try(p + page_size - i - 1, "", i, "");
        /* start of the page, prefixed with the cwd */
        openbsd_try(p, cwd, i, "");
        /* how about at the end of the page, prefixed with cwd? */
        openbsd_try(p + page_size - cwd_len - i - 1, cwd, i, "");

        /* mkstemps() and a non-empty suffix */
        /* try first at the start of a page, no prefix */
        openbsd_try(p, "", i, SUFFIX);
        /* now at the end of the page, no prefix */
        openbsd_try(p + page_size - i - SUFFIX_LEN - 1, "", i, SUFFIX);
        /* start of the page, prefixed with the cwd */
        openbsd_try(p, cwd, i, SUFFIX);
        /* how about at the end of the page, prefixed with cwd? */
        openbsd_try(p + page_size - cwd_len - i - SUFFIX_LEN - 1, cwd, i, SUFFIX);
    }
}
