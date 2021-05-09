/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests lfind
*/

#include "../tests_header.h"
#include "my/cpp-like/iterator.h"
#include "my/search.h"

static int compare_ints(const void *left, const void *right)
{
    return *(const int *)left - *(const int *)right;
}

Test(my_lfind, cloudlibc_zero)
{
    cr_assert_eq(my_lfind((const void *)1, (const void *)2, 0, 3, (int (*)(const void *, const void *))4), NULL);
}

Test(my_lfind, cloudlibc_simple)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = -MY_ARRAY_SIZE(arr); i < 2 * (int)MY_ARRAY_SIZE(arr); ++i) { 
        void *result = my_lfind(&i, arr, MY_ARRAY_SIZE(arr), sizeof(arr[0]), compare_ints);
        if (i < 0 || i >= (int)MY_ARRAY_SIZE(arr))
            cr_assert_eq(result, NULL);
        else
            cr_assert_eq(result, &arr[i]);
    }
}
