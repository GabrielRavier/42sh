/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines get_home_dir
*/

#include "get_home_dir.h"
#include "var.h"
#include "getpwnam.h"

static const shell_char_t HOME[] = {'h', 'o', 'm', 'e', '\0'};

// We specifically ignore NIS special names
static shell_char_t *do_non_empty_username(const shell_char_t *username)
{
    struct passwd *password_file_entry;

    if (*username == '+' || *username == '-')
        return NULL;
    password_file_entry = shell_getpwnam(shell_char_static_xstrdup_to_c(
        username));
    return password_file_entry != NULL ? shell_char_xstrdup_from_c(
        password_file_entry->pw_dir) : NULL;
}

// We check whether we're trying to get the empty username (i.e. us/$home)
// first, and then go get the home directory from the username
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
    return do_non_empty_username(username);
}
