/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Declares stdlib-related entities
*/

#pragma once

#include "features.h"
#include <stdint.h>
#include <stddef.h>

/// Sort an array of num_elements elements of size element_size, pointed to by
/// base. The contents are sorted in ascending order, according to the
/// comparison function pointed to by comparison_function
void my_qsort(void *base, size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *))
    MY_ATTR_NONNULL((1, 4));

struct my_qsort_r_internal_comparison_function_and_argument {
    int (*func)(const void *, const void *, void *);
    void *argument;
};

/// This implements the internal version of my_qsort_r, to avoid restrictions on
/// having more than 5 arguments to a function
void my_internal_qsort_r(void *base, size_t num_elements, size_t element_size,
    const struct my_qsort_r_internal_comparison_function_and_argument *cmp)
    MY_ATTR_NONNULL((1, 4));

/// Same as my_qsort, except comparison_function takes a third argument, which
/// will always be the fourth argument passed to my_qsort_r
MY_ATTR_NONNULL((1, 4)) static inline void my_qsort_r(void *base,
    size_t num_elements, size_t element_size,
    int (*comparison_function)(const void *, const void *, void *),
    void *argument)
{
    my_internal_qsort_r(base, num_elements, element_size,
        (&((struct my_qsort_r_internal_comparison_function_and_argument){
        comparison_function, argument})));
}

void *my_bsearch(const void *key, const void *base, size_t num_elements,
    size_t element_size, int (*cmp)(const void *, const void *))
    MY_ATTR_NONNULL((1, 2, 5)) MY_ATTR_WARN_UNUSED_RESULT;

/// Changes the size of the memory block pointed to by ptr of original_length
/// bytes to new_length bytes.
void *my_realloc_size(void *ptr, size_t new_length, size_t original_length)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_NOTHROW MY_ATTR_ALLOC_SIZE((2))
    MY_ATTR_MALLOC;

/// This allows an arbitrary amount of signs before the number, and handles them
/// appropriately, so this doesn't behave exactly identically to strtol. It also
/// does not set errno
long my_strtol_base_str(const char *num_ptr, char **end_num_ptr,
    const char *base) MY_ATTR_NONNULL((1, 3)) MY_ATTR_NOTHROW;

/// This is the actual strtol. Converts a string to a long integer.
long my_strtol(const char *MY_RESTRICT num_ptr, char **MY_RESTRICT end_num_ptr,
    int base) MY_ATTR_NONNULL((1)) MY_ATTR_NOTHROW;

/// Converts a string to a long long integer.
long long my_strtoll(const char *MY_RESTRICT num_ptr,
    char **MY_RESTRICT end_num_ptr, int base) MY_ATTR_NONNULL((1))
    MY_ATTR_NOTHROW;

/// Converts a string to an unsigned long integer.
unsigned long my_strtoul(const char *MY_RESTRICT num_ptr,
    char **MY_RESTRICT end_num_ptr, int base) MY_ATTR_NONNULL((1))
    MY_ATTR_NOTHROW;

/// Converts a string to an unsigned long long integer.
unsigned long long my_strtoull(const char *MY_RESTRICT num_ptr,
    char **MY_RESTRICT end_num_ptr, int base) MY_ATTR_NONNULL((1))
    MY_ATTR_NOTHROW;

/// Computes the absolute value of an integer
int my_abs(int x) MY_ATTR_NOTHROW MY_ATTR_CONST MY_ATTR_WARN_UNUSED_RESULT;

/// Causes abnormal process termination
void my_abort(void) MY_ATTR_NOTHROW MY_ATTR_NORETURN;

/// Return the value of an environment variable, or NULL if it doesn't exist
char *my_getenv(const char *name) MY_ATTR_NOTHROW MY_ATTR_NONNULL((1))
    MY_ATTR_WARN_UNUSED_RESULT;

// Change or add name in the environment, setting it to value unless it already
// exists and overwrite is non-zero
int my_setenv(const char *name, const char *value, int overwrite)
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((2));

// Remove the given name from the environment. It is not an error if name does
// not exist in the environment
int my_unsetenv(const char *name) MY_ATTR_NOTHROW MY_ATTR_NONNULL((1));

// Generates a unique temporary filename from template, of which the last six
// characters must be "XXXXXX" (which are replaced with characters that make the
// filename unique). This returns a file descriptor to that file (open for
// reading and writing), or -1 if it fails to do so
int my_mkstemp(char *template) MY_ATTR_NONNULL((1)) MY_ATTR_WARN_UNUSED_RESULT;

// Same as my_mkstemp, but template may contain a suffix after the Xs, of which
// the length shall be suffix_length
int my_mkstemps(char *template, int suffix_length) MY_ATTR_NONNULL((1))
    MY_ATTR_WARN_UNUSED_RESULT;

// Tries to allocate the asked-for amount of memory
void *my_malloc(size_t size) MY_ATTR_NOTHROW MY_ATTR_MALLOC
    MY_ATTR_ALLOC_SIZE((1)) MY_ATTR_WARN_UNUSED_RESULT;

// Version of my_malloc that either succeeds or doesn't return
void *my_xmalloc(size_t size) MY_ATTR_NOTHROW MY_ATTR_MALLOC
    MY_ATTR_ALLOC_SIZE((1)) MY_ATTR_WARN_UNUSED_RESULT;

// Tries to allocate the asked-for amount of members of the specified size and
// initialize them to 0
void *my_calloc(size_t num_members, size_t size) MY_ATTR_NOTHROW MY_ATTR_MALLOC
    MY_ATTR_ALLOC_SIZE((1, 2)) MY_ATTR_WARN_UNUSED_RESULT;

// Version of my_calloc that either succeeds or doesn't return
void *my_xcalloc(size_t num_members, size_t size) MY_ATTR_NOTHROW MY_ATTR_MALLOC
    MY_ATTR_ALLOC_SIZE((1, 2)) MY_ATTR_WARN_UNUSED_RESULT;

// Tries to allocate the asked-for amount of members of the specified size and
// initialize them to 0
void *my_realloc(void *ptr, size_t size) MY_ATTR_NOTHROW MY_ATTR_ALLOC_SIZE((2))
    MY_ATTR_WARN_UNUSED_RESULT;

// Version of my_realloc that either succeeds or doesn't return
void *my_xrealloc(void *ptr, size_t size) MY_ATTR_NOTHROW
    MY_ATTR_ALLOC_SIZE((2)) MY_ATTR_WARN_UNUSED_RESULT;

// Free a block allocated by my_malloc
void my_free(void *ptr) MY_ATTR_NOTHROW;

static inline void my_free_ptr(void *ptr)
{
    my_free(*(void **)ptr);
}

#define MY_CLEANUP_FREE __attribute__((cleanup(my_free_ptr)))

// Terminates program execution with the given status
_Noreturn void my__exit(int status) MY_ATTR_NOTHROW;
