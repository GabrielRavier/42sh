/*
** EPITECH PROJECT, 2021
** mysh
** File description:
** Declares dir
*/

#pragma once

#include "../shell.h"
#include "../dir.h"

enum {
    SHELL_DIR_CMD_OPT_PRINT = 0x1,
    SHELL_DIR_CMD_OPT_LONG = 0x2,
    SHELL_DIR_CMD_OPT_VERTICAL = 0x4,
    SHELL_DIR_CMD_OPT_N = 0x10,
    SHELL_DIR_CMD_OPT_OWD = 0x20,
};

typedef struct {
    struct shell *self;
    shell_char_t ***argv;
    const char *options;
    const char *usage;
    int *result;
} sdcpo_opts_t;

// The options string must be in the order given in the flags enum
bool shell_dir_command_parse_options(sdcpo_opts_t *o);

// The flags here are the SHELL_DIR_CMD_OPT ones
void shell_dir_set_current(struct shell *self, struct dir *dir, int flags);
void shell_dir_print_stack(struct shell *self, int flags);

// This will deal with all the bullshit like trying with the destination as a
// variable name or stuff like that
shell_char_t *shell_dir_do_cmd_chdir(struct shell *self,
    const shell_char_t *destination, bool is_owd);
