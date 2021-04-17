/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines mkstemps
*/

#include "my/stdlib.h"
#include "my/unistd.h"
#include "my/fcntl.h"
#include "my/string.h"
#include "my/sys/time.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <stdbool.h>

static const char LETTERS[] =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static uint64_t rnd_buffer;

// We fill in the random bits in each iteration, try to open the file (return it
// if we succeed), for TMP_MAX iterations. 7777 is basically just a random value
static bool do_loop(int *fd, char *template, char *x_es)
{
    uint64_t rnd_tmp;

    for (size_t count = 0; count < TMP_MAX; ++count) {
        rnd_tmp = rnd_buffer;
        for (size_t i = 0; i < 6; ++i) {
            x_es[i] = LETTERS[rnd_tmp % 62];
            rnd_tmp /= 62;
        }
        *fd = my_open(template, O_RDWR | O_CREAT | O_EXCL, 0600);
        if (*fd >= 0)
            return true;
        rnd_buffer += 7777;
    }
    template[0] = '\0';
    *fd = -1;
    return false;
}

// The gettimeofday/getpid calls are to get more or less random data
int my_mkstemps(char *template, int suffix_length)
{
    size_t template_length = my_strlen(template);
    struct timeval tv;
    int fd;

    if ((ssize_t)template_length < suffix_length + 6 || my_strncmp(
        &template[template_length - 6 - suffix_length], "XXXXXX", 6)) {
        errno = EINVAL;
        return -1;
    }
    my_gettimeofday(&tv, NULL);
    rnd_buffer += ((uint64_t)tv.tv_usec << 16) ^ tv.tv_sec ^ my_getpid();
    if (!do_loop(&fd, template, &template[template_length - 6 - suffix_length]))
        template[0] = '\0';
    return fd;
}
