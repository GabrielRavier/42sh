/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declares entities related to unistd.h
*/

#pragma once

#include "features.h"
#include <sys/types.h>

/// Duplicates the actions of the shell in searching for an executable file
/// (using PATH) if the given filename doesn't contain a /
int my_execvp(const char *file, char *const argv[]) MY_ATTR_NOTHROW
    MY_ATTR_NONNULL((1, 2));

/// Executes execve with the given arguments, and envp being environ
int my_execv(const char *pathname, char *const argv[]) MY_ATTR_NOTHROW
    MY_ATTR_NONNULL((1, 2));

/// Replaces the current process with the program at pathname, with the passed
/// arguments and environment
int my_execve(const char *pathname, char *const argv[], char *const envp[])
    MY_ATTR_NOTHROW MY_ATTR_NONNULL((1, 2));

/// Reads num_bytes into buffer from fd. Returns the amount of bytes read (0 for
/// EOF, -1 for error)
ssize_t my_read(int fd, void *buffer, size_t num_bytes)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_ACCESS((write_only, 2, 3));

/// Write num_bytes from buffer into fd. Returns the amount of bytes written (-1
/// for error)
ssize_t my_write(int fd, const void *buffer, size_t num_bytes)
    MY_ATTR_WARN_UNUSED_RESULT MY_ATTR_ACCESS((read_only, 2, 3));

/// Returns whether fd is a valid fd associated with a terminal
int my_isatty(int fd) MY_ATTR_NOTHROW;

/// Close fd
int my_close(int fd) MY_ATTR_NOTHROW;

/// Move fd's file position depending on offset and whence
off_t my_lseek(int fd, off_t offset, int whence) MY_ATTR_NOTHROW;

/// Returns the process ID of the caller
pid_t my_getpid(void) MY_ATTR_NOTHROW;

/// Remove the pathname name from the filesystem
int my_unlink(const char *pathname) MY_ATTR_NOTHROW MY_ATTR_NONNULL((1));

pid_t my_getpgrp(void) MY_ATTR_NOTHROW;
