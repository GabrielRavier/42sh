/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests mkstemp
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "mktemp_netbsd_check_mode.h"
#include "mkstemp_openbsd_check.h"
#include "mkstemp_openbsd_startup.h"
#include "my/stdio.h"
#include "my/sys/stat.h"
#include <unistd.h>
#include <sys/mman.h>
#include <limits.h>

Test(my_mkstemp, netbsd_basic)
{
    char template[] = "/tmp/mktemp.XXXXXX";

    int fd = my_mkstemp(template);
    cr_assert_neq(fd, -1);

    cr_assert_eq(my_strncmp(template, "/tmp/mktemp.", 12), 0);
    cr_assert_eq(my_write(fd, "X", 1), 1);

    struct stat stat_buffer;
    cr_assert_eq(my_fstat(fd, &stat_buffer), 0);
    mktemp_netbsd_check_mode(&stat_buffer, 0600, false);
}

static void openbsd_try(char *path, const char *prefix, size_t x_len)
{
    size_t prefix_len = my_strlen(prefix);

    for (size_t i = 0; i < 100; ++i) {
        my_memcpy(path, prefix, prefix_len);
        my_memset(path + prefix_len, 'X', x_len);
        path[prefix_len + x_len] = '\0';
        if (mkstemp_openbsd_check(my_mkstemp(path), path, prefix, prefix_len, "", 0, x_len))
            return;
    }
    cr_assert(false && "Failed to successfully pass checks after 100 tries");
}

Test(my_mkstemp, openbsd)
{
    char cwd[PATH_MAX + 1];
    size_t cwd_len;
    long page_size;
    char *p;
    mkstemp_openbsd_startup(cwd, &cwd_len, &page_size, &p);

    for (size_t i = 11; i-- != 0;) {
        /* try first at the start of a page, no prefix */
        openbsd_try(p, "", i);

        /* now at the end of the page, no prefix */
        openbsd_try(p + page_size - i - 1, "", i);

        /* start of the page, prefixed with the cwd */
        openbsd_try(p, cwd, i);

        /* how about at the end of the page, prefixed with cwd? */
        openbsd_try(p + page_size - cwd_len - i - 1, cwd, i);
    }
}

Test(my_mkstemp, gnulib)
{
    cr_assert_eq(chdir("/tmp"), 0);

    char temp_dir[] = "test.mkstemp.XXXXXX";
    cr_assert_neq(mkdtemp(temp_dir), NULL);

    off_t large = (off_t)4294967295u;
    if (large < 0)
        large = 2147483647;

    umask(0);
    for (size_t i = 0; i < 80; ++i) {
        char *template;
        cr_assert_geq(my_asprintf(&template, "%s/coXXXXXX", temp_dir), 0);

        int fd = my_mkstemp(template);
        my_free(template);

        cr_assert_geq(fd, 0);

        cr_assert_eq(my_lseek(fd, large, SEEK_SET), large);

        struct stat stat_buffer;
        cr_assert_eq(my_fstat(fd, &stat_buffer), 0);

        cr_assert_eq(stat_buffer.st_mode & 0077, 0);
        cr_assert_eq(my_close(fd), 0);
    }
}

Test(my_mkstemp, defora)
{
    char template[] = "/tmp/stdlib-test.XXXXXX";

    int fd = my_mkstemp(template);
    cr_assert_geq(fd, 0);

    cr_assert_eq(my_unlink(template), 0);
    cr_assert_eq(my_close(fd), 0);
}

Test(my_mkstemp, libc_test)
{
    char template[] = "/dev/null/fooXXXX";

    int fd = my_mkstemp(template);
    cr_assert_eq(fd, -1);
    cr_assert_eq(my_memcmp(template, "/dev/null/fooXXXX", sizeof(template)), 0);
    cr_assert_eq(errno, EINVAL);
}
