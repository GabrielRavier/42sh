/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines misc tests for FILE stuff
*/

#include "../tests_header.h"
#include "my/cpp-like/algorithm.h"
#include "my/stdio.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <unistd.h>
#include <errno.h>

// Add the rest of this once we have fprintf, fwprintf, fputs or fputwc
Test(my_stdio, bionic_cantwrite)
{
    my_file_t *fp = my_fopen("/proc/version", "r");

    errno = 0;
    cr_assert_eq(my_putc('x', fp), EOF);
    cr_assert_eq(errno, EBADF);

    errno = 0;
    cr_assert_eq(my_fputc('x', fp), EOF);
    cr_assert_eq(errno, EBADF);

    errno = 0;
    cr_assert_eq(my_fprintf(fp, "hello"), EOF);
    cr_assert_eq(errno, EBADF);

    errno = 0;
    cr_assert_eq(my_fwrite("hello", 1, 2, fp), 0);
    cr_assert_eq(errno, EBADF);

    errno = 0;
    cr_assert_eq(my_fputs("hello", fp), EOF);
    cr_assert_eq(errno, EBADF);
}

static void cloudlibc_random_pair(size_t max, size_t *a, size_t *b)
{
    size_t total = random() % (max + 1);
    *a = random() % (total + 1);
    *b = (*a == 0) ? (size_t)random() : total / *a;
}

static void cloudlibc_random_string(char *buffer, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        buffer[i] = random();
        if (buffer[i] == '\0')
            buffer[i] = 1;
    }
    buffer[length] = '\0';
}

#if 0
#define LOG_DEBUG printf
#else
#define LOG_DEBUG(...)
#endif

static void cloudlibc_do_random_test(my_file_t *fp)
{
    unsigned char contents[1024] = {0};
    bool has_error = false;
    bool has_eof = false;
    off_t offset = 0;
    off_t length = 0;
    unsigned char pushbacks[100];
    size_t num_pushbacks = 0;

    for (size_t i = 0; i < 10000; ++i) {
        switch (random() % 11) {
        case 0:
            LOG_DEBUG("ferror(fp) == %d\n", has_error);
            cr_assert_eq((bool)my_ferror(fp), has_error);
            break;
        case 1:
            LOG_DEBUG("fflush\n");
            cr_assert_eq(my_fflush(fp), 0);
            break;
        case 2:
            if (offset < (off_t)sizeof(contents)) {
                unsigned int c = random();
                LOG_DEBUG("fputc(%u, fp) -> %u\n", c, (unsigned char)c);
                cr_assert_eq(my_fputc(c, fp), (unsigned char)c);
                contents[offset++] = c;
                if (length < offset)
                    length = offset;
                num_pushbacks = 0;
            }
            break;
        case 3:
            if (offset < (off_t)sizeof(contents)) {
                unsigned int c = random();
                LOG_DEBUG("putc(%u, fp) -> %u\n", c, (unsigned char)c);
                cr_assert_eq(my_putc(c, fp), (unsigned char)c);
                contents[offset++] = c;
                if (length < offset)
                    length = offset;
                num_pushbacks = 0;
            }
            break;
        case 4:
        {
            size_t size, count;
            cloudlibc_random_pair(sizeof(contents) - offset, &size, &count);
            LOG_DEBUG("fwrite(following_buffer, %zu, %zu, fp)\n", size, count);

            char write_buffer[sizeof(contents)];
            size_t write_length = size * count;
            for (size_t j = 0; j < write_length; ++j) {
                write_buffer[j] = random();
                LOG_DEBUG("byte %zu: %u\n", j, write_buffer[j]);
            }

            size_t result = write_length == 0 ? 0 : count;
            cr_assert_eq(my_fwrite(write_buffer, size, count, fp), result);

            if (write_length != 0) {
                my_memcpy(contents + offset, write_buffer, write_length);
                offset += write_length;
                length = MY_MAX(length, offset);
                num_pushbacks = 0;
            }
            break;
        }
        case 5:
            LOG_DEBUG("feof\n");
            cr_assert_eq((bool)my_feof(fp), has_eof);
            break;
        case 6:
        {
            LOG_DEBUG("fputs\n");
            size_t write_length = random() % (sizeof(contents) - offset + 1);
            char write_buffer[sizeof(contents) + 1];
            cloudlibc_random_string(write_buffer, write_length);

            cr_assert_geq(my_fputs(write_buffer, fp), 0);

            if (write_length != 0) {
                my_memcpy(contents + offset, write_buffer, write_length);
                offset += write_length;
                length = MY_MAX(length, offset);
                num_pushbacks = 0;
            }
            break;
        }
        case 7:
        {
            int c = my_fgetc(fp);
            LOG_DEBUG("fgetc(fp) -> %d\n", c);
            if (num_pushbacks > 0)
                cr_assert_eq(c, pushbacks[--num_pushbacks]);
            else if (offset < length)
                cr_assert_eq(c, contents[offset++]);
            else {
                cr_assert_eq(c, EOF);
                has_eof = true;
            }
            break;
        }
        case 8:
        {
            int c = my_getc(fp);
            LOG_DEBUG("getc(fp) -> %d\n", c);
            if (num_pushbacks > 0)
                cr_assert_eq(c, pushbacks[--num_pushbacks]);
            else if (offset < length)
                cr_assert_eq(c, contents[offset++]);
            else {
                cr_assert_eq(c, EOF);
                has_eof = true;
            }
            break;
        }
        case 9:
            if (num_pushbacks < sizeof(pushbacks)) {
                unsigned int c = random();
                LOG_DEBUG("ungetc(%u, fp) -> %u\n", c, (unsigned char)c);
                if ((int)c == EOF)
                    cr_assert_eq(my_ungetc(c, fp), EOF);
                else
                    cr_assert_eq(my_ungetc(c, fp), (unsigned char)c);
                if ((int)c != EOF) {
                    pushbacks[num_pushbacks++] = c;
                    has_eof = false;
                }
            }
            break;
        case 10:
        {
            char write_buffer[sizeof(contents) + 1];
            size_t write_length = random() % (sizeof(contents) - offset + 1);
            cloudlibc_random_string(write_buffer, write_length);
            cr_assert_eq(my_fprintf(fp, "%s", write_buffer), (int)write_length);
            if (write_length != 0) {
                my_memcpy(contents + offset, write_buffer, write_length);
                offset += write_length;
                length = MY_MAX(length, offset);
                num_pushbacks = 0;
            }
            break;
        }
        default:
            cr_assert(false && "Should NEVER be reached");
        }
        cr_assert_geq(offset, 0);
        cr_assert_leq(offset, (off_t)sizeof(contents));
        cr_assert_geq(length, 0);
        cr_assert_leq(length, (off_t)sizeof(contents));
    }
    cr_assert_eq(my_fclose(fp), 0);
}

Test(my_stdio, cloudlibc_random)
{
    char *filename = tmpnam(NULL);

    for (size_t i = 0; i < 100; ++i) {
        my_file_t *fp = my_fopen(filename, "w+");
        cloudlibc_do_random_test(fp);
    }
}

// Add the rest of this once we have clearerr, freopen, getchar, fgets, gets,
// fread, remove, rename, tmpnam and tmpfile
Test(my_stdio, plauger)
{
    char *filename = tmpnam(NULL);
    my_file_t *fp = my_fopen(filename, "w");

    cr_assert_neq(fp, NULL);
    cr_assert_neq(fp, my_stdin);
    cr_assert_neq(fp, my_stdout);
    cr_assert_neq(fp, my_stderr);
    cr_assert_eq(my_feof(fp), 0);
    cr_assert_eq(my_ferror(fp), 0);
    cr_assert_eq(my_feof(fp), 0);
    cr_assert_eq(my_ferror(fp), 0);
    cr_assert_eq(my_fgetc(fp), EOF);
    cr_assert_eq(my_feof(fp), 0);
    cr_assert_neq(my_ferror(fp), 0);
}

Test(my_stdio, picolibc_posix_io)
{
    char template[] = "/tmp/libmy-picolibc-posix-io-test.XXXXXX";
    cr_assert_neq(mkdtemp(template), NULL);
    cr_assert_eq(chdir(template), 0);

    static const char *FILENAME = "posix-io-test-file";
    my_file_t *fp = my_fopen(FILENAME, "w");
    cr_assert_neq(fp, NULL);

    static const char *TEST_STRING = "hello, world\n";
    cr_assert_eq((size_t)my_fprintf(fp, "%s", TEST_STRING), my_strlen(TEST_STRING));
    cr_assert_eq(my_fclose(fp), 0);

    fp = my_fopen(FILENAME, "r");
    cr_assert_neq(fp, NULL);

    const char *it = TEST_STRING;
    while (true) {
        int c = (random() & 1 ? &my_getc : &my_fgetc)(fp);
        if (c == EOF)
            break;
        cr_assert_eq(c, *it++);
    }
    cr_assert_eq(*it, '\0');
}
