/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines path
*/

#include "../init.h"
#include "../import_env_path.h"
#include "../../shell_char.h"
#include "my/stdlib.h"
#include <stdlib.h>

bool shell_init_path(struct shell *self)
{
    const char *env_path = getenv("PATH");
    shell_char_t *as_shell_char = shell_char_xstrdup_from_c(env_path ?
        env_path : "/usr/bin:/bin");
    bool result;

    result = shell_import_env_path(self, as_shell_char);
    my_free(as_shell_char);
    return result;
}
