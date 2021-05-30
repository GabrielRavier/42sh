/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Defines cleanup_fds
*/

#include "cleanup_fds.h"
#include "open.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/param.h>

// We avoid closing sockets because we never create them but stuff like NSS
// modules might
void shell_cleanup_fds(struct shell *self)
{
    struct stat stat_buffer;

    for (int fd = 0; fd < NOFILE; ++fd)
        if (fd != self->input_fd && fd != self->output_fd && fd !=
            self->error_output_fd && fd != self->old_stdin_fd && fd !=
            SHELL_TTY_FD && fstat(fd, &stat_buffer) == 0 && !S_ISSOCK(
            stat_buffer.st_mode)) {
            close(fd);
            if (fd < 3)
                shell_open("/dev/null", O_RDONLY);
        }
}
