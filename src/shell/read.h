/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares read
*/

#pragma once

#include "../shell.h"

typedef struct {
    struct shell *self;
    int fd;
    void *buf;
    size_t count;
    ssize_t *result;
} sr_opts_t;

bool shell_read(sr_opts_t *o);
