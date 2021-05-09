/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests that use several search.h functions
*/

#include "../tests_header.h"
#include "my/search.h"

static int compare_ints(const void *left, const void *right)
{
    return *(const int *)left - *(const int *)right;
}

Test(my_search, bionic_lfind_lsearch)
{
    int arr[10] = {0};
    size_t arr_size = 0;

    int needle = 2;
    cr_assert_eq(my_lfind(&needle, arr, arr_size, sizeof(arr[0]), compare_ints), NULL);
    // Finish this once we do lsearch
}
