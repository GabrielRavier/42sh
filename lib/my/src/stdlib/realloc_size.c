/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines realloc_size
*/

#include "my/stdlib.h"
#include "my/string.h"

#if LIBMY_HAS_LIBC_REALLOC

void *my_realloc_size(void *ptr, size_t new_length, size_t original_length)
{
    (void)original_length;
    return my_realloc(ptr, new_length);
}
#else
static void *handle_other_cases(void *ptr, size_t new_length,
    size_t original_length)
{
    void *new_ptr;

    if (new_length <= original_length)
        return ptr;
    new_ptr = my_malloc(new_length);
    if (new_ptr != NULL) {
        my_memcpy(new_ptr, ptr, original_length);
        my_free(ptr);
    }
    return new_ptr;
}

void *my_realloc_size(void *ptr, size_t new_length, size_t original_length)
{
    if (new_length == 0) {
        my_free(ptr);
        return NULL;
    }
    if (ptr == NULL)
        return my_malloc(new_length);
    return handle_other_cases(ptr, new_length, original_length);
}
#endif
