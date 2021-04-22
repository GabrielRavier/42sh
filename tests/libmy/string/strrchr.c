/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Defines strrchr
*/

#include "../tests_header.h"
#include "my/string.h"
#include "bionic_test_state.h"
#include "glibc.h"
#include "../bionic_buffer.h"
#include "my/cpp-like/algorithm.h"
#include "my/cpp-like/iterator.h"
#include <limits.h>

Test(my_strrchr, newlib)
{
    static const char *const abcd = "abcd";

    cr_assert_eq(my_strrchr(abcd, 'z'), NULL);
    cr_assert_eq(my_strrchr(abcd, 'c'), abcd + 2);
    cr_assert_eq(my_strrchr(abcd, 'd'), abcd + 3);
    cr_assert_eq(my_strrchr(abcd, 'a'), abcd);
    cr_assert_eq(my_strrchr(abcd, '\0'), abcd + 4);

    static const char *const ababa = "ababa";
    cr_assert_eq(my_strrchr(ababa, 'b'), ababa + 3);

    static const char *const null = "";
    cr_assert_eq(my_strrchr(null, 'b'), NULL);
    cr_assert_eq(my_strrchr(null, '\0'), null);
}

Test(my_strrchr, escape)
{
    static const char *const abcdefabc = "abcdefabc";

    cr_assert_eq(my_strrchr(abcdefabc, 'a'), abcdefabc + 6);
    cr_assert_eq(my_strrchr(abcdefabc, 'b'), abcdefabc + 7);
    cr_assert_eq(my_strrchr(abcdefabc, 'c'), abcdefabc + 8);
    cr_assert_eq(my_strrchr(abcdefabc, 'g'), NULL);
    cr_assert_eq(my_strrchr(abcdefabc, 'd'), abcdefabc + 3);
}

Test(my_strrchr, netbsd_basic)
{
    static struct {
        const char *value;
        bool match;
        ssize_t offset_first;
        ssize_t offset_last;
    } const table[] = {
        { "",                   0, 0, 0 },
        { "a",                  0, 0, 0 },
        { "aa",                 0, 0, 0 },
        { "abc",                0, 0, 0 },
        { "abcd",               0, 0, 0 },
        { "abcde",              0, 0, 0 },
        { "abcdef",             0, 0, 0 },
        { "abcdefg",            0, 0, 0 },
        { "abcdefgh",           0, 0, 0 },

        { "/",                  1, 0, 0 },
        { "//",                 1, 0, 1 },
        { "/a",                 1, 0, 0 },
        { "/a/",                1, 0, 2 },
        { "/ab",                1, 0, 0 },
        { "/ab/",               1, 0, 3 },
        { "/abc",               1, 0, 0 },
        { "/abc/",              1, 0, 4 },
        { "/abcd",              1, 0, 0 },
        { "/abcd/",             1, 0, 5 },
        { "/abcde",             1, 0, 0 },
        { "/abcde/",            1, 0, 6 },
        { "/abcdef",            1, 0, 0 },
        { "/abcdef/",           1, 0, 7 },
        { "/abcdefg",           1, 0, 0 },
        { "/abcdefg/",          1, 0, 8 },
        { "/abcdefgh",          1, 0, 0 },
        { "/abcdefgh/",         1, 0, 9 },

        { "a/",                 1, 1, 1 },
        { "a//",                1, 1, 2 },
        { "a/a",                1, 1, 1 },
        { "a/a/",               1, 1, 3 },
        { "a/ab",               1, 1, 1 },
        { "a/ab/",              1, 1, 4 },
        { "a/abc",              1, 1, 1 },
        { "a/abc/",             1, 1, 5 },
        { "a/abcd",             1, 1, 1 },
        { "a/abcd/",            1, 1, 6 },
        { "a/abcde",            1, 1, 1 },
        { "a/abcde/",           1, 1, 7 },
        { "a/abcdef",           1, 1, 1 },
        { "a/abcdef/",          1, 1, 8 },
        { "a/abcdefg",          1, 1, 1 },
        { "a/abcdefg/",         1, 1, 9 },
        { "a/abcdefgh",         1, 1, 1 },
        { "a/abcdefgh/",        1, 1, 10 },

        { "ab/",                1, 2, 2 },
        { "ab//",               1, 2, 3 },
        { "ab/a",               1, 2, 2 },
        { "ab/a/",              1, 2, 4 },
        { "ab/ab",              1, 2, 2 },
        { "ab/ab/",             1, 2, 5 },
        { "ab/abc",             1, 2, 2 },
        { "ab/abc/",            1, 2, 6 },
        { "ab/abcd",            1, 2, 2 },
        { "ab/abcd/",           1, 2, 7 },
        { "ab/abcde",           1, 2, 2 },
        { "ab/abcde/",          1, 2, 8 },
        { "ab/abcdef",          1, 2, 2 },
        { "ab/abcdef/",         1, 2, 9 },
        { "ab/abcdefg",         1, 2, 2 },
        { "ab/abcdefg/",        1, 2, 10 },
        { "ab/abcdefgh",        1, 2, 2 },
        { "ab/abcdefgh/",       1, 2, 11 },

        { "abc/",               1, 3, 3 },
        { "abc//",              1, 3, 4 },
        { "abc/a",              1, 3, 3 },
        { "abc/a/",             1, 3, 5 },
        { "abc/ab",             1, 3, 3 },
        { "abc/ab/",            1, 3, 6 },
        { "abc/abc",            1, 3, 3 },
        { "abc/abc/",           1, 3, 7 },
        { "abc/abcd",           1, 3, 3 },
        { "abc/abcd/",          1, 3, 8 },
        { "abc/abcde",          1, 3, 3 },
        { "abc/abcde/",         1, 3, 9 },
        { "abc/abcdef",         1, 3, 3 },
        { "abc/abcdef/",        1, 3, 10 },
        { "abc/abcdefg",        1, 3, 3 },
        { "abc/abcdefg/",       1, 3, 11 },
        { "abc/abcdefgh",       1, 3, 3 },
        { "abc/abcdefgh/",      1, 3, 12 },

        { "abcd/",              1, 4, 4 },
        { "abcd//",             1, 4, 5 },
        { "abcd/a",             1, 4, 4 },
        { "abcd/a/",            1, 4, 6 },
        { "abcd/ab",            1, 4, 4 },
        { "abcd/ab/",           1, 4, 7 },
        { "abcd/abc",           1, 4, 4 },
        { "abcd/abc/",          1, 4, 8 },
        { "abcd/abcd",          1, 4, 4 },
        { "abcd/abcd/",         1, 4, 9 },
        { "abcd/abcde",         1, 4, 4 },
        { "abcd/abcde/",        1, 4, 10 },
        { "abcd/abcdef",        1, 4, 4 },
        { "abcd/abcdef/",       1, 4, 11 },
        { "abcd/abcdefg",       1, 4, 4 },
        { "abcd/abcdefg/",      1, 4, 12 },
        { "abcd/abcdefgh",      1, 4, 4 },
        { "abcd/abcdefgh/",     1, 4, 13 },

        { "abcde/",             1, 5, 5 },
        { "abcde//",            1, 5, 6 },
        { "abcde/a",            1, 5, 5 },
        { "abcde/a/",           1, 5, 7 },
        { "abcde/ab",           1, 5, 5 },
        { "abcde/ab/",          1, 5, 8 },
        { "abcde/abc",          1, 5, 5 },
        { "abcde/abc/",         1, 5, 9 },
        { "abcde/abcd",         1, 5, 5 },
        { "abcde/abcd/",        1, 5, 10 },
        { "abcde/abcde",        1, 5, 5 },
        { "abcde/abcde/",       1, 5, 11 },
        { "abcde/abcdef",       1, 5, 5 },
        { "abcde/abcdef/",      1, 5, 12 },
        { "abcde/abcdefg",      1, 5, 5 },
        { "abcde/abcdefg/",     1, 5, 13 },
        { "abcde/abcdefgh",     1, 5, 5 },
        { "abcde/abcdefgh/",    1, 5, 14 },

        { "abcdef/",            1, 6, 6 },
        { "abcdef//",           1, 6, 7 },
        { "abcdef/a",           1, 6, 6 },
        { "abcdef/a/",          1, 6, 8 },
        { "abcdef/ab",          1, 6, 6 },
        { "abcdef/ab/",         1, 6, 9 },
        { "abcdef/abc",         1, 6, 6 },
        { "abcdef/abc/",        1, 6, 10 },
        { "abcdef/abcd",        1, 6, 6 },
        { "abcdef/abcd/",       1, 6, 11 },
        { "abcdef/abcde",       1, 6, 6 },
        { "abcdef/abcde/",      1, 6, 12 },
        { "abcdef/abcdef",      1, 6, 6 },
        { "abcdef/abcdef/",     1, 6, 13 },
        { "abcdef/abcdefg",     1, 6, 6 },
        { "abcdef/abcdefg/",    1, 6, 14 },
        { "abcdef/abcdefgh",    1, 6, 6 },
        { "abcdef/abcdefgh/",   1, 6, 15 },

        { "abcdefg/",           1, 7, 7 },
        { "abcdefg//",          1, 7, 8 },
        { "abcdefg/a",          1, 7, 7 },
        { "abcdefg/a/",         1, 7, 9 },
        { "abcdefg/ab",         1, 7, 7 },
        { "abcdefg/ab/",        1, 7, 10 },
        { "abcdefg/abc",        1, 7, 7 },
        { "abcdefg/abc/",       1, 7, 11 },
        { "abcdefg/abcd",       1, 7, 7 },
        { "abcdefg/abcd/",      1, 7, 12 },
        { "abcdefg/abcde",      1, 7, 7 },
        { "abcdefg/abcde/",     1, 7, 13 },
        { "abcdefg/abcdef",     1, 7, 7 },
        { "abcdefg/abcdef/",    1, 7, 14 },
        { "abcdefg/abcdefg",    1, 7, 7 },
        { "abcdefg/abcdefg/",   1, 7, 15 },
        { "abcdefg/abcdefgh",   1, 7, 7 },
        { "abcdefg/abcdefgh/",  1, 7, 16 },

        { "abcdefgh/",          1, 8, 8 },
        { "abcdefgh//",         1, 8, 9 },
        { "abcdefgh/a",         1, 8, 8 },
        { "abcdefgh/a/",        1, 8, 10 },
        { "abcdefgh/ab",        1, 8, 8 },
        { "abcdefgh/ab/",       1, 8, 11 },
        { "abcdefgh/abc",       1, 8, 8 },
        { "abcdefgh/abc/",      1, 8, 12 },
        { "abcdefgh/abcd",      1, 8, 8 },
        { "abcdefgh/abcd/",     1, 8, 13 },
        { "abcdefgh/abcde",     1, 8, 8 },
        { "abcdefgh/abcde/",    1, 8, 14 },
        { "abcdefgh/abcdef",    1, 8, 8 },
        { "abcdefgh/abcdef/",   1, 8, 15 },
        { "abcdefgh/abcdefg",   1, 8, 8 },
        { "abcdefgh/abcdefg/",  1, 8, 16 },
        { "abcdefgh/abcdefgh",  1, 8, 8 },
        { "abcdefgh/abcdefgh/", 1, 8, 17 },
    };

    char buffer[100];
    for (size_t i = 0; i < sizeof(long); ++i)
        for (size_t j = 0; j < MY_ARRAY_SIZE(table); ++j) {
            my_strcpy(&buffer[i], table[j].value);

            const char *offset = my_strrchr(&buffer[i], '/');

            if (!table[j].match)
                cr_assert_eq(offset, NULL);
            else
                cr_assert_eq(table[j].offset_last, offset - &buffer[i]);

            cr_assert_eq(offset, my_strrchr(&buffer[i], 0xFFFFFF00 | '/'));
        }
}

Test(my_strrchr, l4os)
{
    static const char *const ineedbread = "ineedbread";

    cr_assert_eq(my_strrchr(ineedbread, 'e'), ineedbread + 7);
    cr_assert_eq(my_strrchr(ineedbread, 'c'), NULL);
    cr_assert_eq(my_strrchr(ineedbread, '\0'), ineedbread + my_strlen(ineedbread));
}

Test(my_strrchr, stlport)
{
    static const char *const foofoo = "foofoo";

    cr_assert_eq(my_strrchr(foofoo, 'f'), foofoo + 3);
}

Test(my_strrchr, reactos_shlwapi)
{
    char string[129];

    for (size_t i = 32; i < 128; ++i)
        string[i] = i;
    string[128] = '\0';

    for (size_t i = 32; i < 128; ++i)
        cr_assert_eq(my_strrchr(string + 32, i) - string, (ptrdiff_t)i);
    for (size_t i = 32; i < 128; ++i)
        cr_assert_eq(my_strrchr(string + i + 1, i), NULL);
}

Test(my_strrchr, skiboot)
{
    static const char *const hello_world = "Hello World!";

    cr_assert_eq(my_strrchr(hello_world, 'H'), hello_world);
    cr_assert_eq(my_strrchr(hello_world, 'o'), hello_world + 7);
    cr_assert_eq(my_strrchr(hello_world, 'a'), NULL);
    cr_assert_eq(my_strrchr(hello_world, 'l'), hello_world + 9);
    cr_assert_eq(my_strrchr(hello_world, '!'), hello_world + 11);
}

static void avr_libc_check(const char *str, int c, ssize_t offset)
{
    const char *result = my_strrchr(str, c);

    if (offset == -1)
        cr_assert_eq(result, NULL);
    else
        cr_assert_eq(str + offset, result);
}

Test(my_strrchr, avr_libc)
{
    // Not found
    avr_libc_check("", 1, -1);
    avr_libc_check("", 255, -1);
    avr_libc_check("ABCDEF", 'a', -1);

    // Found
    avr_libc_check("\001", 1, 0);
    avr_libc_check("\337", 0337, 0);
    avr_libc_check("987654321", '7', 2);

    // '\0' is part of a string
    avr_libc_check("12345", 0, 5);
    avr_libc_check("", 0, 0);

    // Last occurence
    avr_libc_check("00", '0', 1);
    avr_libc_check("abcdabcd", 'b', 5);
    avr_libc_check("***********", '*', 10);

    // Properly converted to char
    avr_libc_check("ABCDEF", 'A' + 0x100, 0);
    avr_libc_check("ABCDE\377", ~0, 5);
    avr_libc_check("+", ~0xFF, 1);

    avr_libc_check("................................................................................................................................................................................................................................................................*...............", '*', 256);
}

Test(my_strrchr, bionic)
{
    static const int seek_char = 'M';
    struct bionic_test_state state = bionic_test_state_new(1024);

    for (size_t i = 1; i < state.n; ++i) {
        for (bionic_test_state_begin_iters(&state); bionic_test_state_has_next_iter(&state); bionic_test_state_next_iter(&state)) {
            if (~seek_char > 0)
                my_memset(state.ptr1, ~seek_char, state.lengths[i]);
            else
                my_memset(state.ptr1, 1, state.lengths[i]);
            state.ptr1[state.lengths[i] - 1] = '\0';

            size_t position = random() % state.max_length;
            const char *expected;
            if (position >= state.lengths[i] - 1)
                expected = seek_char == '\0' ? state.ptr1 + state.lengths[i] - 1 : NULL;
            else {
                state.ptr1[position] = seek_char;
                expected = state.ptr1 + position;
            }
            cr_assert_eq(strrchr(state.ptr1, seek_char), expected);
        }
    }
    bionic_test_state_destroy(&state);
}

static void bionic_do_strrchr_single_buffer_test(uint8_t *buffer, size_t length)
{
    if (length >= 1) {
        char value = 32 + (length % 96);
        my_memset(buffer, value, length - 1);
        buffer[length - 1] = '\0';

        char search_value = 33 + (length % 96);
        cr_assert_eq(my_strrchr((char *)buffer, search_value), NULL);
        cr_assert_eq(my_strrchr((char *)buffer, '\0'), (char *)&buffer[length - 1]);

        if (length >= 2) {
            buffer[0] = search_value;
            cr_assert_eq(my_strrchr((char *)buffer, search_value), (char *)&buffer[0]);

            buffer[0] = value;
            buffer[length - 2] = search_value;
            cr_assert_eq(my_strrchr((char *)buffer, search_value), (char *)&buffer[length - 2]);
        }
    }
}

Test(my_strrchr, bionic_align)
{
    bionic_run_single_buffer_align_test(4096, bionic_do_strrchr_single_buffer_test);
}

Test(my_strrchr, bionic_overread)
{
    bionic_run_single_buffer_overread_test(bionic_do_strrchr_single_buffer_test);
}

Test(my_strrchr, cloudlibc)
{
    static const char *const hello_world = "Hello, world";

    cr_assert_eq(my_strrchr(hello_world, 'A'), NULL);
    cr_assert_eq(my_strrchr(hello_world, 'o'), hello_world + 8);
    cr_assert_eq(my_strrchr(hello_world, '\0'), hello_world + 12);
}

Test(my_strrchr, dietlibc)
{
    static const char *const foo_bar_baz = "foo bar baz";

    cr_assert_eq(my_strrchr(foo_bar_baz, 'z'), foo_bar_baz + 10);
    cr_assert_eq(my_strrchr(foo_bar_baz, ' '), foo_bar_baz + 7);
    cr_assert_eq(my_strrchr(foo_bar_baz, 'x'), NULL);
}

static void glibc_do_test(size_t alignment, size_t position, size_t length, int seek_char, int max_char)
{
    alignment &= 7;
    if ((alignment + length) >= glibc_page_size)
        return;

    char *const buffer = glibc_buf1;
    for (size_t i = 0; i < length; ++i) {
        buffer[alignment + i] = (random() * random()) & max_char;
        if (buffer[alignment + i] == '\0')
            buffer[alignment + i] = (random() * random()) & max_char;
        if (buffer[alignment + i] == '\0')
            buffer[alignment + i] = 1;
        if ((i > position || position >= length) && buffer[alignment + i] == seek_char)
            buffer[alignment + i] = seek_char + 10 + (random() & 15);
    }
    buffer[alignment + length] = '\0';

    char *expected;
    if (position < length) {
        buffer[alignment + position] = seek_char;
        expected = buffer + alignment + position;
    } else
        expected = (seek_char == 0) ? buffer + alignment + length : NULL;
    cr_assert_eq(my_strrchr(buffer + alignment, seek_char), expected);
}

static void glibc_do_random_tests(void)
{
    unsigned char *p = (unsigned char *)(glibc_buf1 + glibc_page_size) - 512;

    for (size_t n = 0; n < 10000; ++n) {
        size_t alignment = random() & (63 / sizeof(char));
        size_t position = random() & 511;
        if (position + alignment > 511)
            position = 510 - alignment - (random() & 7);

        size_t length = random() & 511;
        if (position >= length)
            length = position + (random() & 7);
        if (length + alignment >= 512)
            length = 511 - alignment - (random() & 7);

        int seek_char = random() & 255;
        if (seek_char != '\0' && position == length) {
            if (position != 0)
                --position;
            else
                ++length;
        }
        size_t j = MY_MIN(length + alignment + 64, (size_t)512);

        for (size_t i = 0; i < j; ++i) {
            if (i == position + alignment)
                p[i] = seek_char;
            else if (i == length + alignment)
                p[i] = 0;
            else {
                p[i] = random() & 255;
                if (((i > position + alignment && i < length + alignment) || position > length) && p[i] == seek_char)
                    p[i] = seek_char + 13;
                if (i < length + alignment && p[i] == '\0') {
                    p[i] = seek_char - 13;
                    if (p[i] == '\0')
                        p[i] = 140;
                }
            }
        }

        const char *expected =
            (position <= length) ? (char *)(p + position + alignment) :
            (seek_char == 0) ? (char *)(p + length + alignment) : NULL;
        cr_assert_eq(my_strrchr((char *)(p + alignment), seek_char), expected);
    }
}

Test(my_strrchr, glibc)
{
    glibc_test_string_init();
    for (size_t i = 1; i < 8; ++i) {
        glibc_do_test(0, 16 << i, 2048, 23, 127);
        glibc_do_test(i, 16 << i, 2048, 23, 127);
    }
    for (size_t i = 1; i < 8; ++i) {
        glibc_do_test(0, 64, 256, 23, CHAR_MAX);
        glibc_do_test(i, 64, 256, 23, CHAR_MAX);
    }
    for (size_t i = 1; i < 32; ++i) {
        glibc_do_test(0, i, i + 1, 23, 127);
        glibc_do_test(0, i, i + 1, 23, CHAR_MAX);
    }
    for (size_t i = 1; i < 8; ++i) {
        glibc_do_test(0, 16 << i, 2048, 0, 127);
        glibc_do_test(i, 16 << i, 2048, 0, 127);
    }
    for (size_t i = 1; i < 8; ++i) {
        glibc_do_test(0, 64, 256, 0, CHAR_MAX);
        glibc_do_test(i, 64, 256, 0, CHAR_MAX);
    }
    for (size_t i = 1; i < 32; ++i) {
        glibc_do_test(0, i, i + 1, 0, 127);
        glibc_do_test(0, i, i + 1, 0, CHAR_MAX);
    }
    glibc_do_random_tests();
}

Test(my_strrchr, glibc2)
{
    char buf[4096];
    for (size_t i = 0; i < 0x100; ++i) {
        char *p = (char *)((uintptr_t)(buf + 0xFF) & ~0xFF) + i;
        my_strcpy(p, "OK");
        my_strcpy(p + 3, "BAD/WRONG");
        cr_assert_eq(my_strrchr(p, '/'), NULL);
    }
}
