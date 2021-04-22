/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines mkstemp_openbsd_check
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/cpp-like/algorithm.h"
#include "my/unistd.h"
#include "my/string.h"
#include <sys/stat.h>
#include <errno.h>

static inline bool mkstemp_openbsd_check(int fd, const char *path, const char *prefix, size_t prefix_len, const char *suffix, size_t suffix_len, size_t x_len)
{
    if (x_len < 6) {
        cr_assert_lt(fd, 0);
        cr_assert_eq(errno, EINVAL);
        return true;
    }
    cr_assert_geq(fd, 0);

    struct stat stat_buffer, file_stat_buffer;
    cr_assert_eq(stat(path, &stat_buffer), 0);
    cr_assert_eq(stat(path, &file_stat_buffer), 0);
    cr_assert_eq(stat_buffer.st_dev, file_stat_buffer.st_dev);
    cr_assert_eq(stat_buffer.st_ino, file_stat_buffer.st_ino);
    my_close(fd);
    cr_assert_eq(my_memcmp(path, prefix, prefix_len), 0);
    cr_assert_eq(my_memcmp(path + prefix_len + x_len, suffix, suffix_len + 1), 0);
    for (const char *i = MY_MAX(path + prefix_len, path + prefix_len + x_len - 6); i < path + prefix_len + x_len; ++i) {
        cr_assert_neq(*i, '\0');
        if (*i == 'X')
            return false;
    }
    return true;
}
