/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests putenv
*/

#include "../tests_header.h"
#include "my/stdlib.h"
#include "my/string.h"

Test(my_putenv, freebsd_putenv_basic)
{
    char string[1024];

    my_strcpy(string, "crap=true");
    cr_assert_eq(putenv(string), 0);
    cr_assert_eq(my_getenv("crap"), getenv("crap"));
    string[1] = 'l';
    cr_assert_eq(my_getenv("clap"), getenv("clap"));
    cr_assert_eq(my_getenv("crap"), getenv("crap"));
    string[1] = 'r';
    cr_assert_eq(my_unsetenv("crap"), 0);
    cr_assert_eq(my_getenv("crap"), getenv("crap"));
}
