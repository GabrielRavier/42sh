/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines import_env_path
*/

#include "import_env_path.h"
#include "var.h"
#include "my/stdlib.h"
#include "var.h"

static const shell_char_t DOT[] = {'.', '\0'};
static const shell_char_t PATH[] = { 'p', 'a', 't', 'h', '\0' };

static void do_loop(shell_char_t *env_path, shell_char_t **path_array,
    size_t *i)
{
    shell_char_t c;
    shell_char_t *env_it = env_path;

    while (true) {
        c = *env_path;
        if (c == ':' || c == '\0') {
            *env_path = '\0';
            path_array[(*i)++] = shell_char_xstrdup(*env_it != '\0' ? env_it :
                DOT);
            if (c != '\0') {
                env_it = env_path + 1;
                *env_path = ':';
            } else
                break;
        }
        ++env_path;
    }
}

bool shell_import_env_path(struct shell *self, shell_char_t *env_path)
{
    size_t num_colons = 0;
    shell_char_t **path_array;
    size_t i;

    for (i = 0; env_path[i] != '\0'; ++i)
        if (env_path[i] == ':')
            ++num_colons;
    path_array = my_xcalloc(num_colons + 2, sizeof(*path_array));
    i = 0;
    if (*env_path != '\0')
        do_loop(env_path, path_array, &i);
    path_array[i] = NULL;
    return shell_var_set_valv(self, PATH, path_array, VAR_FLAG_READ_WRITE);
}
