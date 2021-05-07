/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines search
*/

#include "my/features.h"
#include <stddef.h>

void *my_lfind(const void *key, const void *base, size_t num_members,
    size_t element_size, int (*cmp)(const void *, const void *))
    MY_ATTR_NONNULL((1, 2, 5)) MY_ATTR_WARN_UNUSED_RESULT;
