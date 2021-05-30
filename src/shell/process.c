/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines process
*/

#include "process.h"
#include "flush_output_buffer.h"
#include "lex.h"
#include "parse_tree.h"
#include "execute.h"
#include "print_error.h"
#include "printf.h"
#include "signal.h"
#include "cleanup_fds.h"
#include "my/stdio.h"
#include <unistd.h>

MY_ATTR_WARN_UNUSED_RESULT static bool do_line_lex_part(struct shell *self)
{
    int old_disable_sigint;
    bool result;

    if (self->should_set_interrupts && !shell_signal_enable_sigint(self,
        &old_disable_sigint))
        return false;
    lexical_word_list_free(&self->current_lexical_word);
    result = shell_lex(self, &self->current_lexical_word);
    if (self->should_set_interrupts)
        self->disable_sigint = old_disable_sigint;
    return result;
}

MY_ATTR_WARN_UNUSED_RESULT static bool do_line(struct shell *self)
{
    struct shell_parse_tree *parse_tree;
    bool result = true;

    if (!do_line_lex_part(self))
        return false;
    parse_tree = shell_parse_tree_from_lex_tree(self,
        self->current_lexical_word.next,
        &self->current_lexical_word, 0);
    if (self->error.text != NULL) {
        shell_parse_tree_free(parse_tree);
        return false;
    }
    result = shell_execute(&((se_opts_t){self, parse_tree, NULL, NULL,
        (self->terminal_pgrp > 0 ? self->terminal_pgrp : -1)}));
    shell_parse_tree_free(parse_tree);
    return result;
}

MY_ATTR_WARN_UNUSED_RESULT static bool do_inner_pre_line(struct shell *self)
{
    if (self->done_input) {
        self->done_input = false;
        return false;
    }
    if (self->check_stop != 0) {
        --self->check_stop;
        shell_printf(self, "Decremented check_stop to %d\n", self->check_stop);
    }
    if (self->input_is_tty) {
        shell_printf(self, "> ");
        shell_flush_output_buffer(self);
    }
    return true;
}

// We catch all the errors at the top of the while (or die). We cleanup any
// potentially accidentally left-open files here
// We make sure to continue dying if we haven't been told to continue on error
MY_ATTR_WARN_UNUSED_RESULT static bool do_loop(struct shell *self,
    bool no_out_on_error)
{
    while (true) {
        if (self->error.text != NULL)
            shell_print_error(self);
        shell_proc_end_job(self);
        if (self->handling_error) {
            if (!no_out_on_error) {
                self->done_input = false;
                return false;
            }
            self->handling_error = false;
            shell_cleanup_fds(self);
            continue;
        }
        if (!do_inner_pre_line(self))
            break;
        if (!do_line(self))
            continue;
    }
    return true;
}

bool shell_process(struct shell *self, bool no_out_on_error)
{
    ++self->exit_set;
    if (!do_loop(self, no_out_on_error))
        return false;
    --self->exit_set;
    return shell_signal_handle_pending(self);
}
