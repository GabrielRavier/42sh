/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines term
*/

#include "../init.h"
#include "../var.h"
#include "my/string.h"
#include <stdlib.h>

static const shell_char_t TERM[] = {'t', 'e', 'r', 'm', '\0'};

bool shell_init_term(struct shell *self)
{
    const char *env_term = getenv("TERM");

    if (env_term != NULL && !shell_var_set_val(self, TERM,
        shell_char_str_quote(shell_char_xstrdup_from_c(env_term)),
        VAR_FLAG_READ_WRITE))
        return false;
    return true;
}
