/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests _exit
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <sys/types.h>
#include <limits.h>

static void do_one_test(int exit_status)
{
    pid_t pid = fork();
    if (pid == 0)
        my__exit(exit_status);

    int status_child;
    cr_assert_neq(waitpid(pid, &status_child, 0), -1);
    cr_assert_eq(WIFSIGNALED(status_child), 0);
    cr_assert_eq(WIFSTOPPED(status_child), 0);
    cr_assert_neq(WIFEXITED(status_child), 0);
    cr_assert_eq(WEXITSTATUS(status_child), exit_status & 0xFF);
}

Test(my__exit, all_8_bit_and_a_bit_more)
{
    for (int32_t i = -10; i != UINT8_MAX + 10; ++i)
        do_one_test(i);
}

Test(my__exit, near_int_min)
{
    for (int i = INT_MIN; i != INT_MIN + 50; ++i)
        do_one_test(i);
}

Test(my__exit, near_int_max)
{
    for (int i = INT_MAX; i != INT_MAX - 50; --i)
        do_one_test(i);
}
