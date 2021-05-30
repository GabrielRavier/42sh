/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Declares write
*/

#pragma once

#include <sys/types.h>
#include <stddef.h>

ssize_t shell_write(int fd, const void *buf, size_t count);
