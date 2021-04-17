/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines bsearch
*/

#include "my/stdlib.h"

void *my_bsearch(const void *key, const void *base, size_t num_elements,
    size_t element_size, int (*cmp)(const void *, const void *))
{
    char *begin = (char *)base;
    char *end = (char *)base + (num_elements - 1) * element_size;
    char *current_middle;
    int comparison_result;

    while (end >= begin) {
        current_middle = begin + element_size * ((num_elements - 1) / 2);
        comparison_result = cmp(key, current_middle);
        if (comparison_result == 0)
            return (current_middle);
        if (comparison_result < 0)
            end = current_middle - element_size;
        else
            begin = current_middle + element_size;
        num_elements = (end - begin) / element_size + 1;
    }
    return NULL;
}
