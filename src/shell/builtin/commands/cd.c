/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin cd
*/

#include "../commands.h"
#include "cd_part2.h"
#include "../../set_error.h"
#include "../../get_number.h"
#include "../../var.h"
#include "../../dir.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include "my/ctype.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

static const shell_char_t OWD[] = {'o', 'w', 'd', '\0'};
static const shell_char_t HOME[] = {'h', 'o', 'm', 'e', '\0'};

static bool try_from_plus(struct shell *self, const shell_char_t *destination,
    int flags)
{
    struct dir *dir;
    char *tmp;

    if (!find_from_plus(self, destination, &dir))
        return false;
    if (dir == NULL)
        return true;
    self->force_print_directory_stack = true;
    tmp = shell_char_static_xstrdup_to_c(dir->name);
    if (chdir(tmp) < 0) {
        shell_set_error(self, SHELL_ERROR_SYSTEM, tmp, strerror(errno));
        return false;
    }
    self->current_dir->prev->next = self->current_dir->next;
    self->current_dir->next->prev = self->current_dir->prev;
    dir_free(self->current_dir);
    shell_dir_set_current(self, dir, flags);
    return false;
}

static shell_char_t *do_cd_home(struct shell *self)
{
    const shell_char_t *destination = shell_var_get_value(self, HOME);

    if (*destination == '\0') {
        shell_set_error(self, SHELL_ERROR_FLAG_NAME |
            SHELL_ERROR_NO_HOME_DIRECTORY);
        return NULL;
    }
    if (chdir(shell_char_static_xstrdup_to_c(destination)) < 0) {
        shell_set_error(self, SHELL_ERROR_FLAG_NAME |
            SHELL_ERROR_CANT_CHANGE_TO_HOME_DIR);
        return NULL;
    }
    return shell_char_xstrdup(destination);
}

static shell_char_t *do_cd(struct shell *self, const shell_char_t *destination,
    int flags, shell_char_t *const *const argv)
{
    self->force_print_directory_stack = false;
    if (destination == NULL)
        return do_cd_home(self);
    if ((flags & SHELL_DIR_CMD_OPT_OWD) == 0 && argv[1] != NULL) {
        shell_set_error(self, SHELL_ERROR_FLAG_NAME |
            SHELL_ERROR_TOO_MANY_ARGUMENTS);
        return NULL;
    }
    if (!try_from_plus(self, destination, flags))
        return NULL;
    return shell_dir_do_cmd_chdir(self, destination, flags &
        SHELL_DIR_CMD_OPT_OWD);
}

void shell_builtin_cd(struct shell *self, shell_char_t **argv)
{
    int flags;
    shell_char_t *destination_copied;
    struct dir *dir;

    if (!shell_dir_command_parse_options(&((sdcpo_opts_t){self, &argv, "plvn",
        "[-|<dir>]", &flags})))
        return;
    destination_copied = do_cd(self, (flags & SHELL_DIR_CMD_OPT_OWD) ?
        shell_var_get_value(self, OWD) : *argv, flags, argv);
    if (destination_copied == NULL)
        return;
    dir = my_xcalloc(1, sizeof(*dir));
    dir->name = destination_copied;
    dir->next = self->current_dir->next;
    dir->prev = self->current_dir->prev;
    dir->prev->next = dir;
    dir->next->prev = dir;
    dir_free(self->current_dir);
    shell_dir_set_current(self, dir, flags);
}
