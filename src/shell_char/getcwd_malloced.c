/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines getcwd_malloced
*/

#include "../shell_char.h"
#include "my/stdlib.h"
#include <unistd.h>
#include <errno.h>
#include <limits.h>

shell_char_t *shell_char_getcwd_malloced(void)
{
    size_t buffer_length = PATH_MAX;
    MY_CLEANUP_FREE char *buffer = my_xmalloc(buffer_length);

    while (getcwd(buffer, buffer_length) == NULL) {
        if (errno != ERANGE)
            return NULL;
        buffer = my_realloc_size(buffer, buffer_length * 2, buffer_length);
        buffer_length *= 2;
    }
    return *buffer == '\0' ? NULL : shell_char_xstrdup_from_c(buffer);
}
