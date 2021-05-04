#!/usr/bin/env bash

# Note: Extra arguments to tests_binary should be given as arguments to this script

# Execute tests from the directory that which contains the script
cd "$(dirname "$0")"

TESTS_BINARY=$(realpath ../../lib/my/tests_binary)
TESTS_SUPPRESSIONS=$(realpath lsan_suppressions)

# We suppress certain memory leaks and all printf errors to avoid problems with our printf tests
LSAN_OPTIONS=suppressions=${TESTS_SUPPRESSIONS}:print_suppressions=0 ASAN_OPTIONS=check_printf=0 $TESTS_BINARY $@

# Wait for all tests to be over before exiting
wait
