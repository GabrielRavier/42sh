/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines do_tcsh
*/

#include "../glob.h"
#include "../get_home_dir.h"
#include "../set_error.h"
#include "my/stdlib.h"

static const size_t SIZE_INCR = 100;

typedef struct {
    struct shell *self;
    const shell_char_t *home_dir;
    const shell_char_t *username;
    const shell_char_t *str;
    shell_char_t **result;
} ft_opts_t;

static bool finish_tilde(ft_opts_t *o)
{
    if (o->home_dir == NULL) {
        if (*o->username != '\0')
            shell_set_error(o->self, SHELL_ERROR_UNKNOWN_USER,
                shell_char_static_xstrdup_to_c(o->username));
        else
            shell_set_error(o->self, SHELL_ERROR_NO_HOME_VAR_SET);
        return false;
    }
    *o->result = (o->home_dir[0] == '/' && o->home_dir[1] == '\0' &&
        o->str[0] == '/') ? shell_char_xstrdup(o->str) :
        shell_char_alloc_concat(o->home_dir, o->str);
    return true;
}

static bool tcsh_glob_tilde(struct shell *self,
    const shell_char_t *str, shell_char_t **result)
{
    const shell_char_t *orig = str;
    MY_CLEANUP_FREE shell_char_t *username = NULL;
    MY_CLEANUP_FREE shell_char_t *home_dir = NULL;

    if (str[1] == '~') {
        *result = shell_char_xstrdup(str);
        return true;
    }
    for (++str; *str != '\0' && *str != '/' && *str != ':'; ++str)
        ;
    username = shell_char_xstrndup(orig + 1, str - (orig + 1));
    home_dir = shell_get_home_dir(self, username);
    return finish_tilde(&((ft_opts_t){self, home_dir, username, str, result}));
}

static shell_char_t **make_vec_loop(shell_char_t **start, size_t size,
    const shell_char_t **strv)
{
    shell_char_t **it = start;

    for (const shell_char_t *i = *strv; i != NULL; i = *++strv) {
        *it++ = shell_char_xstrdup(i);
        if (it == &start[size]) {
            start = my_realloc_size(start, sizeof(*start) * (size + SIZE_INCR),
                sizeof(*start) * size);
            it = &start[size];
            size += SIZE_INCR;
        }
        *it = NULL;
    }
    return start;
}

bool shell_glob_do_tcsh(struct shell *self, const shell_char_t **strv,
    shell_char_t ***result)
{
    shell_char_t **start = make_vec_loop(my_xmalloc(sizeof(*start) *
        SIZE_INCR), SIZE_INCR, strv);
    shell_char_t **it = start;

    for (const shell_char_t *i = *it; i != NULL; i = *++it)
        if (*i == '~' && !tcsh_glob_tilde(self, i, it)) {
            shell_char_strv_free(start);
            return false;
        }
    *result = start;
    return true;
}
