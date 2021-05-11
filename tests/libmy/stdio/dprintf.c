/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests dprintf
*/

#include "../tests_header.h"
#include "../temporary_file.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

Test(my_dprintf, cloudlibc_bad)
{
    errno = 0;
    cr_assert_eq(my_dprintf(-1, "Hello, world\n"), -1);
    cr_assert_eq(errno, EBADF);

    int fds[2];
    cr_assert_eq(pipe(fds), 0);
    cr_assert_eq(fcntl(fds[1], F_SETFL, O_NONBLOCK), 0);

    errno = 0;
    cr_assert_eq(my_dprintf(fds[1], "%5000000s", ""), -1);
    cr_assert_eq(errno, EAGAIN);
    cr_assert_eq(my_close(fds[0]), 0);
    cr_assert_eq(my_close(fds[1]), 0);

    cr_assert_eq(pipe(fds), 0);
    cr_assert_eq(my_close(fds[0]), 0);

    signal(SIGPIPE, SIG_IGN);
    errno = 0;
    cr_assert_eq(my_dprintf(fds[1], "Hello"), -1);
    cr_assert_eq(errno, EPIPE);
    cr_assert_eq(my_close(fds[1]), 0);
}

Test(my_dprintf, cloudlibc_simple)
{
    int fds[2];
    cr_assert_eq(pipe(fds), 0);
    cr_assert_eq(my_dprintf(fds[1], "%s, %s", "Hello", "world"), 12);
    cr_assert_eq(my_close(fds[1]), 0);

    char buffer[13];
    cr_assert_eq(my_read(fds[0], buffer, sizeof(buffer)), 12);
    buffer[12] = '\0';
    cr_assert_str_eq(buffer, "Hello, world");
    cr_assert_eq(my_close(fds[0]), 0);
}

Test(my_dprintf, gnulib)
{
    errno = 0;
    cr_assert_eq(my_dprintf(-1, "test"), -1);
    cr_assert_eq(errno, EBADF);

    my_close(99);
    errno = 0;
    cr_assert_eq(my_dprintf(99, "test"), -1);
    cr_assert_eq(errno, EBADF);
}

Test(my_dprintf, bionic)
{
    struct test_temporary_file tf = test_temporary_file_new();

    cr_assert_eq(my_dprintf(tf.fd, "hello\n"), 6);
    my_lseek(tf.fd, 0, SEEK_SET);
    // Finish this once we have fdopen

    test_temporary_file_destroy(&tf);
}
