/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines temporary_file
*/

#pragma once

#include "my/stdlib.h"
#include "my/string.h"
#include "my/unistd.h"

struct test_temporary_file {
    int fd;
    char path[1024];
};

static inline struct test_temporary_file test_temporary_file_new(void)
{
    struct test_temporary_file result;
    my_strcpy(result.path, "/tmp/libmy-test-temporary-file.XXXXXX");
    result.fd = my_mkstemp(result.path);
    return result;
}

static inline void test_temporary_file_destroy(const struct test_temporary_file *self)
{
    my_close(self->fd);
    my_unlink(self->path);
}
