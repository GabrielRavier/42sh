/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests getc
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include "my/fcntl.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

static void gnulib_do_test(int (*func)(my_file_t *))
{
    char dir_template[] = "/tmp/libmy-gnulib-test.XXXXXX";

    cr_assert_neq(mkdtemp(dir_template), NULL);
    cr_assert_eq(chdir(dir_template), 0);

    static const char *FILENAME = "test-getc.txt";
    int fd = my_open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0600);
    cr_assert_geq(fd, 0);

    static const char TEXT[] = "hello world";
    cr_assert_eq(my_write(fd, TEXT, sizeof(TEXT)), sizeof(TEXT));
    cr_assert_eq(my_close(fd), 0);

    // Test error when closing the fd behind the back of stdio
    {
        my_file_t *fp = my_fopen(FILENAME, "r");
        cr_assert_neq(fp, NULL);
        cr_assert_eq(my_close(my_fileno(fp)), 0);

        errno = 0;
        cr_assert_eq(func(fp), EOF);
        cr_assert_eq(errno, EBADF);
        cr_assert_neq(my_ferror(fp), 0);
        my_fclose(fp);
    }

    // Do the rest of this when we have fdopen

    // Cleanup
    my_unlink(FILENAME);
}

Test(my_getc, gnulib)
{
    gnulib_do_test(my_getc);
}

Test(my_fgetc, gnulib)
{
    gnulib_do_test(my_fgetc);
}

static void bionic_do_test(int (*func)(my_file_t *))
{
    my_file_t *fp = my_fopen("/proc/version", "r");
    cr_assert_neq(fp, NULL);

    cr_assert_eq(func(fp), 'L');
    cr_assert_eq(func(fp), 'i');
    cr_assert_eq(func(fp), 'n');
    cr_assert_eq(func(fp), 'u');
    cr_assert_eq(func(fp), 'x');
    my_fclose(fp);
}
