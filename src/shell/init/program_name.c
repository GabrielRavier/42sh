/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Defines program_name
*/

#include "../init.h"
#include "my/string.h"

void shell_init_program_name(struct shell *self, const char *argv0)
{
    const char *strrchr_result = my_strrchr(argv0, '/');

    strrchr_result = strrchr_result != NULL ? strrchr_result + 1 : argv0;
    if (*strrchr_result == '-')
        ++strrchr_result;
    self->program_name = my_xstrdup((strrchr_result != NULL &&
        *strrchr_result != '\0') ? strrchr_result : "mysh");
}
