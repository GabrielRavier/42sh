/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 3 of do_exec
*/

#pragma once

#include "../../../shell.h"
#include "../../parse_tree.h"
#include "do_exec_part4.h"
#include <fcntl.h>
#include <ctype.h>

static const shell_char_t SLASH[] = {'/', '\0'};
static const shell_char_t DOT[] = {'.', '\0'};

// If it looks like a binary, then we error
static void check_if_looks_like_binary(struct shell *self, int fd,
    unsigned char first_two_bytes[2], const char *filename)
{
    ssize_t num_read = read(fd, first_two_bytes, 2);
    int saved_errno;

    if (num_read == 2) {
        if (!isprint(first_two_bytes[0]) && first_two_bytes[0] != '\n' &&
            first_two_bytes[0] != '\t') {
            saved_errno = errno;
            close(fd);
            shell_set_and_print_error(self, SHELL_ERROR_WRONG_ARCHITECTURE,
                filename, strerror(saved_errno));
        }
        else if (num_read >= 0) {
            first_two_bytes[0] = '#';
            first_two_bytes[1] = '\0';
        }
    }
}

// We make sure that it doesn't look like a binary before feeding it to the shell
static void do_noexec(struct shell *self, const char *filename_as_c,
    shell_char_t **argv, const shell_char_t *filename)
{
    int fd = open(filename_as_c, O_RDONLY);
    unsigned char first_two_bytes[2];

    if (fd != -1) {
        check_if_looks_like_binary(self, fd, first_two_bytes, filename_as_c);
        close(fd);
    }
    do_shell_exec(self, filename, argv, fd != 1 && first_two_bytes[0] != '#');
}

static inline void set_exec_error(struct shell *self,
    const shell_char_t *filename)
{
    if (self->exec.error == NULL) {
        self->exec.error = strerror(errno);
        my_free(self->exec.command_path);
        self->exec.command_path = shell_char_xstrdup(filename);
    }
}

// Attempts execution of filename with argv as the argument vector. It records
// the error message if not found (unless we got ENOENT), and will also handle
// shell scripts.
static inline void try_exec(struct shell *self, const shell_char_t *filename,
    shell_char_t **argv)
{
    char **argv_as_c = shell_char_xdup_strv_to_c(argv);
    char *filename_as_c = shell_char_xstrdup_to_c(filename);

    errno = 0;
    execv(filename_as_c, argv_as_c);
    char_strv_free(argv_as_c);
    switch (errno) {
    case ENOEXEC:
        do_noexec(self, filename_as_c, argv, filename);
    case ENOMEM:
        shell_set_and_print_error(self, SHELL_ERROR_SYSTEM, filename_as_c,
            strerror(errno));
        MY_ASSERT(false && "Should never be reached");
    case ENOENT:
        break;
    default:
        set_exec_error(self, filename);
        break;
    }
}

// We append the command name prefixed with a slash to everything in path
// We avoid running a command based on the fact that it's present in the same
// directory, to the point of completely ignoring as part of the path
static inline void do_path_loop(struct shell *self,
    struct shell_parse_tree *parse_tree, const shell_char_t *const *search_path)
{
    shell_char_t *slash_plus_cmd_name = shell_char_alloc_concat(SLASH,
        parse_tree->argv[0]);

    do {
        if (*search_path[0] == '\0' || shell_char_strcmp(*search_path,
            DOT) == 0)
            try_exec(self, parse_tree->argv[0], parse_tree->argv);
        else {
            shell_char_t *executed_filename = shell_char_alloc_concat(
                *search_path, slash_plus_cmd_name);
            try_exec(self, executed_filename, parse_tree->argv);
            my_free(executed_filename);
        }
        ++search_path;
    } while (*search_path != NULL);
    my_free(slash_plus_cmd_name);
}
