/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines command_parse_options
*/

#include "../dir.h"
#include "command_parse_options_part2.h"
#include "../set_error.h"
#include "my/string.h"

static bool do_after_loop(sdcpo_opts_t *o, shell_char_t **i)
{
    if (*i && (*o->result & SHELL_DIR_CMD_OPT_OWD)) {
        shell_set_error(o->self, SHELL_ERROR_DIR_CMD_USAGE,
            shell_char_static_xstrdup_to_c(**o->argv), o->options, o->usage);
        return false;
    }
    *o->argv = i;
    if (*o->result & (SHELL_DIR_CMD_OPT_LONG |
        SHELL_DIR_CMD_OPT_VERTICAL | SHELL_DIR_CMD_OPT_N))
        *o->result &= SHELL_DIR_CMD_OPT_PRINT;
    return true;
}

bool shell_dir_command_parse_options(sdcpo_opts_t *o)
{
    shell_char_t **i;
    bool stop_loop;

    *o->result = 0;
    for (i = *o->argv + 1; *i != NULL && **i == '-'; ++i) {
        if (!do_loop_it(&((dli_opts_t){o->self, o->argv, &i, o->result,
            o->options, o->usage, &stop_loop})))
            return false;
        if (stop_loop)
            break;
    }
    return do_after_loop(o, i);
}
