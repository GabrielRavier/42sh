/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines grap_pgrp
*/

#include "../tty.h"
#include <unistd.h>
#include <signal.h>
#include <errno.h>

bool shell_tty_grab_pgrp(int fd, pid_t wanted_pgrp)
{
    struct sigaction old_tty_action;
    pid_t tty_pgrp;

    for (size_t i = 0; i < 100; ++i) {
        tty_pgrp = tcgetpgrp(fd);
        if (tty_pgrp == wanted_pgrp)
            return true;
        sigaction(SIGTTIN, NULL, &old_tty_action);
        signal(SIGTTIN, SIG_DFL);
        kill(0, SIGTTIN);
        sigaction(SIGTTIN, &old_tty_action, NULL);
    }
    errno = EPERM;
    return false;
}
