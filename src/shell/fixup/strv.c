/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines strv
*/

#include "../fixup.h"
#include "strv_part2.h"

// We start by setting up the input vector for shell_fixup_read_character
bool shell_fixup_strv(struct shell *self, shell_char_t *const *strv,
    shell_char_t ***result)
{
    struct my_shell_char_ptr_vector *result_vec =
        my_shell_char_ptr_vector_new();
    bool should_continue_loop;

    self->fixup.cur_strv_input = strv;
    self->fixup.cur_str_input = NULL;
    shell_fixup_unget_character(self, 0);
    shell_fixup_unread_character(self, 0);
    while (true) {
        if (!do_word(self, result_vec, &should_continue_loop)) {
            my_shell_char_ptr_vector_destroy(result_vec);
            return false;
        }
        if (!should_continue_loop)
            break;
    }
    my_shell_char_ptr_vector_append_single(result_vec, NULL);
    *result = my_shell_char_ptr_vector_move_buffer(result_vec);
    return true;
}
