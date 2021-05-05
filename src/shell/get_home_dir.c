/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_home_dir
*/

#include "get_home_dir.h"
#include "var.h"

static const shell_char_t HOME[] = {'h', 'o', 'm', 'e', '\0'};

// We'll need getpwnam to be able to do something useful with non-empty
// usernames (TODO: Do that ASAP)
shell_char_t *shell_get_home_dir(struct shell *self,
    const shell_char_t *username)
{
    const shell_char_t *result;

    if (*username == '\0') {
        result = shell_var_get_value(self, HOME);
        if (result != NULL)
            return shell_char_xstrdup(result);
        else
            return NULL;
    }
    return NULL;
}
