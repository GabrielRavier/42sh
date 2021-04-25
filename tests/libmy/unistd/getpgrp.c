/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests getpgrp
*/

#include "my/unistd.h"
#include "../tests_header.h"
#include <unistd.h>

Test(my_getpgrp, basic)
{
    cr_assert_eq(my_getpgrp(), getpgrp());
}
