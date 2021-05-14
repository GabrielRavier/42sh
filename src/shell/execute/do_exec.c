/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines do_exec
*/

#include "do_exec.h"
#include "../parse_tree.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/unistd.h"
#include <stdlib.h>

_Noreturn void shell_execute_do_exec(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    char **argv = shell_char_xdup_strv_to_c(parse_tree->argv);

    my_execvp(argv[0], argv);
    my_dprintf(self->error_output_fd, "%s: Command not found.\n", argv[0]);
    for (size_t i = 0; argv[i] != NULL; ++i)
        my_free(argv[i]);
    my_free(argv);
    exit(1);
}
