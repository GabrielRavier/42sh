/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines parse_tree
*/

#include "../fixup.h"
#include "../parse_tree.h"

bool shell_fixup_parse_tree(struct shell *self,
    struct shell_parse_tree *parse_tree)
{
    shell_char_t **fixuped_argv;

    for (shell_char_t *const *i = parse_tree->argv; *i != NULL; ++i)
        for (const shell_char_t *j = *i; *j != '\0'; ++j)
            if (shell_char_is_type(*j, SHELL_CHAR_TYPE_ALL_QUOTES)) {
                if (!shell_fixup_strv(self, parse_tree->argv, &fixuped_argv))
                    return false;
                shell_char_strv_free(parse_tree->argv);
                parse_tree->argv = fixuped_argv;
                return true;
            }
    return true;
}
