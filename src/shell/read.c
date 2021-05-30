/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines read
*/

#include "read.h"
#include "signal.h"
#include <unistd.h>
#include <errno.h>

bool shell_read(sr_opts_t *o)
{
    *o->result = -1;

    do {
        if (!shell_signal_handle_pending(o->self))
            return false;
        *o->result = read(o->fd, o->buf, o->count);
    } while (*o->result == -1 && errno == EINTR);
    return true;
}
