/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests mkstemp
*/

#include "../tests_header.h"
#include "my/cpp-like/algorithm.h"
#include "my/stdlib.h"
#include "my/stdio.h"
#include "my/string.h"
#include "my/unistd.h"
#include "my/sys/stat.h"
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <limits.h>

static void netbsd_check_mode(const struct stat *stat_buffer, int mode, bool is_dir)
{
    cr_assert_neq(is_dir ? S_ISDIR(stat_buffer->st_mode) : S_ISREG(stat_buffer->st_mode), 0);
    cr_assert_neq(stat_buffer->st_mode & mode, 0);
}

Test(my_mkstemp, netbsd_basic)
{
    char template[] = "/tmp/mktemp.XXXXXX";

    int fd = my_mkstemp(template);
    cr_assert_neq(fd, -1);

    cr_assert_eq(my_strncmp(template, "/tmp/mktemp.", 12), 0);
    cr_assert_eq(my_write(fd, "X", 1), 1);

    struct stat stat_buffer;
    cr_assert_eq(my_fstat(fd, &stat_buffer), 0);
    netbsd_check_mode(&stat_buffer, 0600, false);
}

static bool openbsd_check(int fd, const char *path, const char *prefix, size_t prefix_len, size_t x_len)
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
    cr_assert_eq(my_memcmp(path + prefix_len + x_len, "", 1), 0);
    for (const char *i = MY_MAX(path + prefix_len, path + prefix_len + x_len - 6); i < path + prefix_len + x_len; ++i) {
        cr_assert_neq(*i, '\0');
        if (*i == 'X')
            return false;
    }
    return true;
}

static void openbsd_try(char *path, const char *prefix, size_t x_len)
{
    size_t prefix_len = my_strlen(prefix);

    for (size_t i = 0; i < 100; ++i) {
        my_memcpy(path, prefix, prefix_len);
        my_memset(path + prefix_len, 'X', x_len);
        path[prefix_len + x_len] = '\0';
        int fd = my_mkstemp(path);
        if (openbsd_check(fd, path, prefix, prefix_len, x_len))
            return;
    }
    cr_assert(false && "Failed to successfully pass checks after 100 tries");
}

Test(my_mkstemp, openbsd)
{
    cr_assert_eq(chdir("/tmp"), 0);

    char cwd[PATH_MAX + 1];
    cr_assert_neq(getcwd(cwd, sizeof(cwd) - 2), NULL);

    size_t cwd_len = my_strlen(cwd);
    cwd[cwd_len++] = '/';
    cwd[cwd_len] = '\0';

    long page_size = sysconf(_SC_PAGESIZE);
    char *p = mmap(NULL, page_size * 3, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    cr_assert_neq(p, MAP_FAILED);
    cr_assert_eq(mprotect(p, page_size, PROT_NONE), 0);
    cr_assert_eq(mprotect(p + page_size * 2, page_size, PROT_NONE), 0);
    p += page_size;

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
