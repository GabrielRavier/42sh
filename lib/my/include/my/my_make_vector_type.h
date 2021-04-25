/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines a my_vector type
*/

#include "my/cpp-like/algorithm.h"
#include "my/assert.h"
#include "my/string.h"
#include "my/stdlib.h"
#include "my/features.h"
#include <stddef.h>

// This macro is used as the type included in the vector
#ifndef MY_VECTOR_TYPE
    #error "MY_VECTOR_TYPE must be defined before including this"
#endif
#ifndef MY_VECTOR_TYPE_NAME
    #error "MY_VECTOR_TYPE_NAME must be defined before including this"
#endif

#define MY_INTERNAL_CONCAT_TOKENS_NX(a, b) a ## b
#define MY_INTERNAL_CONCAT_TOKENS(a, b) MY_INTERNAL_CONCAT_TOKENS_NX(a, b)
#define MY_INTERNAL_TYPE_TOKEN MY_INTERNAL_CONCAT_TOKENS(my_, \
    MY_INTERNAL_CONCAT_TOKENS(MY_VECTOR_TYPE_NAME, _vector))

#define MY_INTERNAL_MAKE_METHOD_NAME(name) MY_INTERNAL_CONCAT_TOKENS(\
    MY_INTERNAL_TYPE_TOKEN, name)

struct MY_INTERNAL_TYPE_TOKEN {
    size_t size;
    size_t allocated_size;
    MY_VECTOR_TYPE *data;
};

// Guarantees that there will be at least self->length + length bytes available
// in the vector
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_guarantee_can_expand)(
    struct MY_INTERNAL_TYPE_TOKEN *self, size_t size)
{
    size_t current_allocated_size = self->allocated_size;

    if (self->size + size >= current_allocated_size) {
        self->allocated_size = MY_MAX(self->size + size + 16,
            self->size * 3 / 2);
        self->data = (MY_VECTOR_TYPE *)my_realloc_size(self->data,
            self->allocated_size * sizeof(*self->data),
            current_allocated_size * sizeof(*self->data));
        MY_ASSERT(self->data != NULL);
    }
    return self;
}

// Creates a new, empty, vector
MY_ATTR_WARN_UNUSED_RESULT static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_new)(void)
{
    struct MY_INTERNAL_TYPE_TOKEN *self =
        (struct MY_INTERNAL_TYPE_TOKEN *)my_xmalloc(sizeof(*self));

    self->size = 0;
    self->allocated_size = 0;
    self->data = NULL;
    return MY_INTERNAL_MAKE_METHOD_NAME(_guarantee_can_expand)(self, 1);
}

// Inserts size bytes from data to self at position. data may not part of self
// (i.e. directly located within self->data)
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_insert)(struct MY_INTERNAL_TYPE_TOKEN *self,
    const MY_VECTOR_TYPE *data, size_t size, size_t position)
{
    if (self == NULL || data == NULL || size == 0 || (position > self->size))
        return self;
    MY_INTERNAL_MAKE_METHOD_NAME(_guarantee_can_expand)(self, size);
    my_memmove(self->data + position + size, self->data + position,
        (self->size - position) * sizeof(*self->data));
    my_memcpy(self->data + position, data, size * sizeof(*self->data));
    self->size += size;
    return self;
}

// Same as insert, but for a single item
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_insert_single)(
    struct MY_INTERNAL_TYPE_TOKEN *self, MY_VECTOR_TYPE item,
    size_t position)
{
    return MY_INTERNAL_MAKE_METHOD_NAME(_insert)(self, &item, 1, position);
}

// Append size items from data to self
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_append)(struct MY_INTERNAL_TYPE_TOKEN *self,
    const MY_VECTOR_TYPE *data, size_t size)
{
    return MY_INTERNAL_MAKE_METHOD_NAME(_insert)(self, data, size,
        self->size);
}

// Same as append, but for a single item
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_append_single)(
    struct MY_INTERNAL_TYPE_TOKEN *self, MY_VECTOR_TYPE item)
{
    return MY_INTERNAL_MAKE_METHOD_NAME(_append)(self, &item, 1);
}

// Creates a new vector from the given data (which has size items)
MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_ACCESS((read_only, 1, 2)) static inline
    struct MY_INTERNAL_TYPE_TOKEN *MY_INTERNAL_MAKE_METHOD_NAME(_new_from_data)
    (const MY_VECTOR_TYPE *data, size_t size)
{
    struct MY_INTERNAL_TYPE_TOKEN *self = MY_INTERNAL_MAKE_METHOD_NAME(_new)();
    if (data)
        MY_INTERNAL_MAKE_METHOD_NAME(_append)(self, data, size);
    return self;
}

// Resizes data to contain size items. If the current size is less than the
// given one, the vector becomes bigger, but has undefined contents after the
// current size. If the current size is greater than the given one, the vector
// is reduced to its first size elements
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_resize)(struct MY_INTERNAL_TYPE_TOKEN *self,
    size_t size)
{
    if (self == NULL)
        return NULL;
    if (size >= self->allocated_size)
        MY_INTERNAL_MAKE_METHOD_NAME(_guarantee_can_expand)(self,
            size - self->size);
    self->size = size;
    return self;
}

// Removes all the items in the vector, as if by using my_vector_resize(self, 0)
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_clear)(struct MY_INTERNAL_TYPE_TOKEN *self)
{
    return MY_INTERNAL_MAKE_METHOD_NAME(_resize)(self, 0);
}

// Copies source into self
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_assign)(struct MY_INTERNAL_TYPE_TOKEN *self,
    const struct MY_INTERNAL_TYPE_TOKEN *source)
{
    if (self == NULL)
        return NULL;
    MY_INTERNAL_MAKE_METHOD_NAME(_resize)(self, source->size);
    my_memcpy(self->data, source->data, self->size * sizeof(*self->data));
    return self;
}

// Remove size items starting at position
static inline struct MY_INTERNAL_TYPE_TOKEN *
    MY_INTERNAL_MAKE_METHOD_NAME(_erase)(struct MY_INTERNAL_TYPE_TOKEN *self,
    size_t position, size_t size)
{
    if (self == NULL || position > self->size || (position + size) > self->size)
        return self;
    my_memmove(self->data + position, self->data + position + size,
        (self->size - (position + size)) * sizeof(*self->data));
    self->size -= size;
    return self;
}

// Destructs the passed vector but returns the underlying buffer
static inline MY_VECTOR_TYPE *
    MY_INTERNAL_MAKE_METHOD_NAME(_move_buffer)(
    struct MY_INTERNAL_TYPE_TOKEN *self)
{
    MY_VECTOR_TYPE *result = self->data;

    my_free(self);
    return result;
}

// Destructs the passed vector and the associated data. If you instead want to
// free the vector but gain ownership of self->data, use my_vector_move_buffer
static inline void MY_INTERNAL_MAKE_METHOD_NAME(_free)(
    struct MY_INTERNAL_TYPE_TOKEN *self)
{
    if (self == NULL)
        return;
    my_free(MY_INTERNAL_MAKE_METHOD_NAME(_move_buffer)(self));
}

#undef MY_INTERNAL_MAKE_METHOD_NAME
#undef MY_INTERNAL_TYPE_TOKEN
#undef MY_INTERNAL_CONCAT_TOKENS
#undef MY_INTERNAL_CONCAT_TOKENS_NX
#undef MY_VECTOR_TYPE_NAME
#undef MY_VECTOR_TYPE

