/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines builtin cd
*/

#include "../commands.h"
#include "../../set_error.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

static void do_it(struct shell *self, const char *destination,
    bool is_home)
{
    if (chdir(destination) != 0) {
        if (is_home)
            shell_set_error(self, SHELL_ERROR_CANT_CHANGE_TO_HOME_DIR);
        else
            shell_set_error(self, SHELL_ERROR_SYSTEM, destination,
                strerror(errno));
    }
}

void shell_builtin_cd(struct shell *self, shell_char_t **argv)
{
    MY_CLEANUP_FREE const char *destination = shell_char_xstrdup_to_c(argv[1]);
    bool is_home = false;

    if (destination == NULL || (destination[0] == '~' &&
        destination[1] == '\0')) {
        destination = my_getenv("HOME");
        if (!destination || *destination == '\0') {
            shell_set_error(self, SHELL_ERROR_NO_HOME_DIRECTORY);
            return;
        }
        is_home = true;
    }
    do_it(self, destination, is_home);
}
