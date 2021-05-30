/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines part 2 of do_exec
*/

#pragma once

#include "../../../shell.h"
#include "../../parse_tree.h"
#include "../../glob.h"
#include "../../print_error.h"
#include "../../set_and_print_error.h"
#include "../../var.h"
#include "my/assert.h"

static const shell_char_t PATH[] = {'p', 'a', 't', 'h', '\0'};

// This is called when we fail to find the command
_Noreturn static inline void exec_print_error(struct shell *self)
{
    if (self->exec.command_path != NULL) {
        self->error_program_name = shell_char_static_xstrdup_to_c(
            self->exec.command_path);
        my_free(self->exec.command_path);
        self->exec.command_path = NULL;
    } else
        self->error_program_name = "";
    if (self->exec.error != NULL)
        shell_set_and_print_error(self, SHELL_ERROR_FLAG_NAME |
            SHELL_ERROR_FORMAT_S, self->exec.error);
    shell_set_and_print_error(self, SHELL_ERROR_FLAG_NAME |
        SHELL_ERROR_COMMAND_NOT_FOUND);
    MY_ASSERT(false && "Should never be reached");
}

static inline shell_char_t **glob_argv_no0(struct shell *self,
    shell_char_t **result)
{
    int glob_flags = shell_glob_strv_get_flags_ncnst(result);

    if (glob_flags != 0) {
        if (!shell_glob_strv_all_ncnst(self, result, glob_flags, &result))
            shell_print_error(self);
        if (result == NULL) {
            self->error_program_name = shell_char_static_xstrdup_to_c(
                self->exec.command_path);
            shell_set_and_print_error(self, SHELL_ERROR_NO_MATCH |
                SHELL_ERROR_FLAG_NAME);
        }
    } else
        result = shell_char_strv_xdup_ncnst(result);
    return result;
}

// Handles the part where we glob the command name
static inline shell_char_t **glob_command_name(struct shell *self,
    shell_char_t *cmd_name_strv[2])
{
    shell_char_t **result;
    int glob_flags = shell_glob_strv_get_flags_ncnst(cmd_name_strv);

    if (glob_flags != 0) {
        if (!shell_glob_strv_all_ncnst(self, cmd_name_strv, glob_flags,
            &result))
            shell_print_error(self);
        if (result == NULL) {
            self->error_program_name = shell_char_static_xstrdup_to_c(
                cmd_name_strv[0]);
            shell_set_and_print_error(self, SHELL_ERROR_NO_MATCH |
                SHELL_ERROR_FLAG_NAME);
        }
    } else
        result = shell_char_strv_xdup_ncnst(cmd_name_strv);
    return result;
}

// If there is no path, only commands starting with / or . are executed
static inline const struct var *do_globbing(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    shell_char_t *cmd_name_strv[2] = {parse_tree->argv[0], NULL};
    shell_char_t **cmd_name_after_glob = glob_command_name(self, cmd_name_strv);
    shell_char_t **argv_no0;
    const struct var *var_path = shell_var_get(self, PATH);

    shell_char_strv_unquote(cmd_name_after_glob);
    self->exec.error = NULL;
    self->exec.command_path = shell_char_xstrdup(cmd_name_after_glob[0]);
    if (var_path == NULL && *cmd_name_after_glob[0] != '/' &&
        *cmd_name_after_glob[0] == '.')
        exec_print_error(self);
    argv_no0 = glob_argv_no0(self, &parse_tree->argv[1]);
    shell_char_strv_free(parse_tree->argv);
    parse_tree->argv = shell_char_strv_alloc_concat(cmd_name_after_glob,
        argv_no0);
    my_free(cmd_name_after_glob);
    my_free(argv_no0);
    return var_path;
}
