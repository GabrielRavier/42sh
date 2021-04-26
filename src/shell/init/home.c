/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines home
*/

#include "../init.h"
#include "../var.h"
#include "my/stdlib.h"

static const shell_char_t HOME[] = {'h', 'o', 'm', 'e', '\0'};

bool shell_init_home(struct shell *self, const shell_char_t **result)
{
    const char *env_home = my_getenv("HOME");
    shell_char_t *home_val = (env_home != NULL) ?
        shell_char_str_quote(shell_char_xstrdup_from_c(env_home)) : NULL;

    if (result)
        if (!shell_var_set_val(self, HOME, home_val, VAR_FLAG_READ_WRITE))
            return false;
    *result = home_val;
    return true;
}
