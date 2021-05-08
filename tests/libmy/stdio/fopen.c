/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests fopen
*/

#include "../tests_header.h"
#include "my/cpp-like/iterator.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include <errno.h>

#include "my/string.h"
#include <limits.h>

Test(my_fopen, netbsd_err)
{
    static const char *MODES[] = {"x", "xr", "xr", "+r+", "R", "W+", " aXX", "Xr", " r+", ""};
    char *filename = tempnam(NULL, NULL);

    my_file_t *fp = my_fopen(filename, "w+");
    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_fclose(fp), 0);

    for (size_t i = 0; i < MY_ARRAY_SIZE(MODES); ++i) {
        errno = 0;
        fp = my_fopen(filename, MODES[i]);
        cr_assert_eq(fp, NULL);
        cr_assert_eq(errno, EINVAL);
    }

    my_unlink(filename);
    my_free(filename);

    errno = 0;
    cr_assert_eq(my_fopen("/usr/bin", "w"), NULL);
    cr_assert_eq(errno, EISDIR);

    errno = 0;
    cr_assert_eq(my_fopen("/a/b/c/d/e/f/g/h/i/j/k", "r"), NULL);
    cr_assert_eq(errno, ENOENT);

    char buffer[PATH_MAX + 2];
    my_memset(buffer, 'x', sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    errno = 0;
    cr_assert_eq(my_fopen(buffer, "r+"), NULL);
    cr_assert_eq(errno, ENAMETOOLONG);
}

Test(my_fopen, netbsd_append)
{
    char *filename = tempnam(NULL, NULL);

    my_file_t *fp = my_fopen(filename, "w+");
    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_fwrite("garbage", 1, 7, fp), 7);
    cr_assert_eq(my_fclose(fp), 0);

    fp = my_fopen(filename, "a");
    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_fwrite("garbage", 1, 7, fp), 7);
    cr_assert_eq(my_fclose(fp), 0);

    // Finish this once we have fread

    my_free(filename);
}

Test(my_fopen, netsbd_mode)
{
    static const char *MODES[] = {"r", "r+", "w", "w+", "a", "a+", "rb", "r+b", "wb", "w+b", "ab", "a+b", "re", "r+e", "we", "w+e", "ae", "a+e", "rf", "r+f", "wf", "w+f", "af", "a+f"};
    char *filename = tempnam(NULL, NULL);

    my_file_t *fp = my_fopen(filename, "w+");
    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_fclose(fp), 0);

    for (size_t i = 0; i < MY_ARRAY_SIZE(MODES); ++i) {
        errno = 0;
        fp = my_fopen(filename, MODES[i]);
        cr_assert_neq(fp, NULL);
        cr_assert_eq(my_fclose(fp), 0);
    }

    my_unlink(filename);
    my_free(filename);
}

Test(my_fopen, netbsd_regular)
{
    errno = 0;
    cr_assert_eq(my_fopen("/bin/cp", "a+"), NULL);
    cr_assert_eq(errno, EACCES);

    errno = 0;
    cr_assert_eq(my_fopen("/bin/cp", "w+"), NULL);
    cr_assert_eq(errno, EACCES);
}
