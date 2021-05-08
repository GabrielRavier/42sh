/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests fprintf
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include "my/unistd.h"
#include <stdlib.h>
#include <unistd.h>

Test(my_fprintf, freebsd_simple_string)
{
    char template[] = "/tmp/libmy-test-fprintf-freebsd-simple-string.XXXXXX";
    cr_assert_eq(mkdtemp(template), template);
    cr_assert_eq(chdir(template), 0);
    
    my_file_t *file = my_fopen("test.txt", "w+");
    cr_assert_neq(file, NULL);

    static const char *CONTENTS = "This is a message";
    cr_assert_eq(my_fprintf(file, "%s", CONTENTS), (int)my_strlen(CONTENTS));
    // Finish this test once we have rewind

    my_fclose(file);
}
