/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests fseterr
*/

#include "../tests_header.h"
#include "my/stdio.h"

Test(my_fseterr, bionic)
{
    my_file_t *fp = my_fopen("/dev/null", "w");
    cr_assert_eq(my_ferror(fp), 0);

    my_fseterr(fp);
    cr_assert_eq(my_ferror(fp), 1);
    my_clearerr(fp);
    cr_assert_eq(my_ferror(fp), 0);

    my_fclose(fp);
}

Test(my_fseterr, gnulib)
{
    cr_assert_eq(my_ferror(my_stdout), 0);
    my_fseterr(my_stdout);
    cr_assert_eq(my_ferror(my_stdout), 1);
    my_clearerr(my_stdout);
    cr_assert_eq(my_ferror(my_stdout), 0);
}
