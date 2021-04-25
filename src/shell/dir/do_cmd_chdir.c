/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines do_cmd_chdir
*/

#include "../dir.h"
#include "../var.h"
#include "../set_error.h"
#include "../glob.h"
#include "my/assert.h"
#include "my/stdlib.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

static shell_char_t *try_var(struct shell *self,
    const shell_char_t *destination)
{
    int saved_errno = errno;
    const shell_char_t *var_value = shell_var_get_value(self, destination);

    if ((var_value[0] == '/' || var_value[0] == '.') && chdir(
        shell_char_static_xstrdup_to_c(var_value)) >= 0)
        return shell_char_getcwd_malloced();
    shell_set_error(self, SHELL_ERROR_SYSTEM,
        shell_char_static_xstrdup_to_c(destination), strerror(saved_errno));
    return NULL;
}

shell_char_t *shell_dir_do_cmd_chdir(struct shell *self,
    const shell_char_t *destination_param, bool is_owd)
{
    MY_CLEANUP_FREE shell_char_t *destination = NULL;

    if (is_owd)
        destination = shell_char_xstrdup(destination_param);
    else if (!shell_glob_str(self, destination_param,
        SHELL_GLOB_STR_FLAG_ERROR, &destination))
        return NULL;
    if (chdir(shell_char_static_xstrdup_to_c(destination)) >= 0)
        return shell_char_getcwd_malloced();
    if (errno != ENOENT && errno != ENOTDIR) {
        shell_set_error(self, SHELL_ERROR_SYSTEM,
            shell_char_static_xstrdup_to_c(destination), strerror(errno));
        return NULL;
    }
    return try_var(self, destination);
}
