/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines do_exec
*/

#include "../do_exec.h"
#include "do_exec_part2.h"
#include "do_exec_part3.h"

static const shell_char_t NUL = '\0';
static const shell_char_t *const DUMMY_PATH_FOR_ONLY_ABSOLUTE[] = {&NUL, NULL};

// If there is no path, nothing in path or a / in the filename, the search is
// restricted
static const shell_char_t *const *get_search_path(const struct var *var_path,
    bool has_slash)
{
    return (var_path == NULL || var_path->valv == NULL ||
        var_path->valv[0] == NULL || has_slash) ? DUMMY_PATH_FOR_ONLY_ABSOLUTE :
        (const shell_char_t **)var_path->valv;
}

// All internal file descriptors are closed on exec, so we don't need to close
// them ourselves, we can just change the fds directly so that error messages
// are handled properly
static void set_internal_file_descriptors(struct shell *self)
{
    self->input_fd = STDIN_FILENO;
    self->output_fd = STDOUT_FILENO;
    self->error_output_fd = STDERR_FILENO;
    self->old_stdin_fd = STDIN_FILENO;
}

// Reset SIGINT and SIGCHLD to make everything work properly
static void unblock_sigint_sigchld(struct shell *self)
{
    sigset_t sigint_sigchld_set;

    sigemptyset(&sigint_sigchld_set);
    sigaddset(&sigint_sigchld_set, SIGINT);
    sigaddset(&sigint_sigchld_set, SIGCHLD);
    sigprocmask(SIG_UNBLOCK, &sigint_sigchld_set, NULL);
    self->disable_sigint = 0;
    self->disable_sigchld = 0;
}

_Noreturn void shell_execute_do_exec(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    const struct var *var_path;
    bool has_slash;

    MY_ASSERT(self->child_depth != 0);
    var_path = do_globbing(self, parse_tree);
    has_slash = strchr(shell_char_static_xstrdup_to_c(self->exec.command_path),
        '/') != NULL;
    shell_char_strv_unquote(parse_tree->argv);
    if (*parse_tree->argv == NULL || **parse_tree->argv == '\0')
        exec_print_error(self);
    set_internal_file_descriptors(self);
    unblock_sigint_sigchld(self);
    if (!do_path_loop(self, parse_tree, get_search_path(var_path, has_slash)))
        shell_print_error(self);
    exec_print_error(self);
    MY_ASSERT(false && "Should never be reached");
}
