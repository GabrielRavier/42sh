/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests ungetc
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/unistd.h"

Test(my_ungetc, dietlibc)
{
    const char *filename = tmpnam(NULL);
    
    my_file_t *fp = my_fopen(filename, "w");
    cr_assert_neq(fp, NULL);

    my_fputs("bla", fp);
    my_fclose(fp);

    fp = my_fopen(filename, "r");
    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_ungetc('z', fp), 'z');
    cr_assert_eq(my_getc(fp), 'z');
    cr_assert_eq(my_getc(fp), 'b');
    cr_assert_eq(my_getc(fp), 'l');
    cr_assert_eq(my_ungetc('m', fp), 'm');
    cr_assert_eq(my_getc(fp), 'm');
    int c = my_getc(fp);
    cr_assert_eq(c, 'a');
    cr_assert_eq(my_getc(fp), EOF);
    cr_assert_neq(my_feof(fp), 0);
    cr_assert_eq(my_ungetc(c, fp), c);
    cr_assert_eq(my_feof(fp), 0);
    cr_assert_eq(my_getc(fp), c);
    cr_assert_eq(my_getc(fp), EOF);
    cr_assert_neq(my_feof(fp), 0);
    my_fclose(fp);

    fp = my_fopen(filename, "r");
    cr_assert_neq(fp, NULL);
    cr_assert_eq(my_getc(fp), 'b');
    cr_assert_eq(my_getc(fp), 'l');
    cr_assert_eq(my_ungetc('b', fp), 'b');
    // Finish this test once we've done fread
    my_fclose(fp);

    my_unlink(filename);
}

Test(my_ungetc, dietlibc2)
{
    my_ungetc(23, my_stdin);
    cr_assert_eq(my_fgetc(my_stdin), 23);
    my_ungetc(230, my_stdin);
    cr_assert_eq(my_fgetc(my_stdin), 230);
}

Test(my_ungetc, picolibc)
{
    cr_assert_eq(my_ungetc('u', my_stdin), 'u');
    cr_assert_eq(my_getc(my_stdin), 'u');
}
