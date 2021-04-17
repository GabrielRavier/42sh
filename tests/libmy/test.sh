#!/usr/bin/env bash

# Execute tests from the directory that which contains the script
cd "$(dirname "$0")"

TESTS_BINARY=$(realpath ../../lib/my/tests_binary)
TESTS_SUPPRESSIONS=$(realpath lsan_suppressions)

# Consider possibly adding ASAN_OPTIONS=check_printf=0 to shut up printf warnings if we really want to

LSAN_OPTIONS=suppressions=${TESTS_SUPPRESSIONS}:print_suppressions=0 $TESTS_BINARY

# Wait for all tests to be over before exiting
wait
