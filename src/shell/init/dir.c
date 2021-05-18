/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines dir
*/

#include "../init.h"
#include "../dir.h"
#include "../exit.h"
#include "../printf.h"
#include "my/stdlib.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static void print_start(struct shell *self, const char *str)
{
    shell_printf(self, "%s: Trying to start from \"%s\"\n", self->program_name,
        str);
}

static shell_char_t *do_handling_if_getcwd_null(struct shell *self,
    shell_char_t *current_dir, const shell_char_t *home_val)
{
    char *home_val_c;
    shell_char_t *result;

    if (current_dir != NULL)
        return current_dir;
    shell_printf(self, "%s: %s\n", self->program_name, strerror(errno));
    if (home_val != NULL && *home_val != '\0') {
        home_val_c = shell_char_static_xstrdup_to_c(home_val);
        print_start(self, home_val_c);
        result = chdir(home_val_c) == -1 ? NULL : shell_char_xstrdup(home_val);
    } else
        result = NULL;
    if (result != NULL)
        return result;
    print_start(self, "/");
    if (chdir("/") == -1)
        shell_exit(self, 1);
    return shell_char_xstrdup_from_c("/");
}

bool shell_init_dir(struct shell *self, const shell_char_t *home_val)
{
    shell_char_t *current_dir = shell_char_getcwd_malloced();
    shell_char_t *cwd_name = do_handling_if_getcwd_null(self, current_dir,
        home_val);
    struct dir *first_cwd = my_xcalloc(1, sizeof(*first_cwd));

    first_cwd->name = cwd_name;
    self->head_dir.next = first_cwd;
    self->head_dir.prev = first_cwd;
    first_cwd->next = &self->head_dir;
    first_cwd->prev = &self->head_dir;
    self->force_print_directory_stack = false;
    return shell_dir_set_current(self, first_cwd, 0);
}
