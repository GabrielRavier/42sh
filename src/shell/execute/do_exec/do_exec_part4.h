/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 4 of do_exec
*/

#pragma once

#include "../../../shell.h"
#include "../../set_and_print_error.h"
#include "../../var.h"
#include "my/assert.h"
#include "my/stdlib.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static const shell_char_t SHELL[] = {'s', 'h', 'e', 'l', 'l', '\0'};
static const shell_char_t SLASH_BIN_SLASH_SH[] = {'/', 'b', 'i', 'n', '/', 's',
    'h', '\0'};

// If executing the shell fails, there isn't much else to do other than just
// throw up our hands and complain we failed
_Noreturn static inline void do_the_shell_execv(struct shell *self,
    const char *filename, char **argv)
{
    execv(filename, argv);
    char_strv_free(argv);
    shell_set_and_print_error(self, SHELL_ERROR_SYSTEM, filename,
        strerror(errno));
    MY_ASSERT(false && "Should never be reached");
}

// We make the new argument list and try to execute the shell. We go to /bin/sh
// (and not $shell) if the shell script does not start with a '#'
_Noreturn static inline void do_shell_exec(struct shell *self,
    const shell_char_t *filename, shell_char_t **argv, bool force_bin_sh)
{
    const shell_char_t **sh_vec = my_xcalloc(2, sizeof(*sh_vec));
    shell_char_t *argv0 = argv[0];
    shell_char_t **old_argv = argv;
    char **argv_as_c;
    const char *filename_as_c;

    sh_vec[0] = shell_var_get(self, SHELL) && !force_bin_sh ?
        shell_var_get_value(self, SHELL) : SLASH_BIN_SLASH_SH;
    sh_vec[1] = NULL;
    argv[0] = (shell_char_t *)filename;
    argv = shell_char_strv_alloc_concat((shell_char_t **)sh_vec, argv);
    old_argv[0] = argv0;
    filename = argv[0];
    argv_as_c = shell_char_xdup_strv_to_c(argv);
    filename_as_c = shell_char_xstrdup_to_c(filename);
    my_free(argv);
    my_free(sh_vec);
    do_the_shell_execv(self, filename_as_c, argv_as_c);
    MY_ASSERT(false && "Should never be reached");
}
