/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines shell_char_vector
*/

#pragma once

#include "shell_char.h"

typedef shell_char_t *shell_char_ptr_t;
#define MY_VECTOR_TYPE shell_char_ptr_t
#define MY_VECTOR_TYPE_NAME shell_char_ptr
#include "my/my_make_vector_type.h"

static inline void my_shell_char_ptr_vector_destroy(
    struct my_shell_char_ptr_vector *self)
{
    for (size_t i = 0; i < self->size; ++i)
        my_free(self->data[i]);
    my_shell_char_ptr_vector_free(self);
}
