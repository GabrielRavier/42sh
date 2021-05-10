#!/usr/bin/env bash

# Execute tests from the directory that which contains the script
cd "$(dirname "$0")"

_42SH=$(realpath ../../42sh)

do_one_test()
{
    _42SH_STDOUT=`mktemp`
    _42SH_STDERR=`mktemp`

    $_42SH <"$1" >$_42SH_STDOUT 2>$_42SH_STDERR
    _42SH_EXIT_STATUS=$?
    [ $_42SH_EXIT_STATUS == $(cat "$2") ] || echo "Incorrect exit status $_42SH_EXIT_STATUS for $1"
    diff -u $_42SH_STDOUT "$3"
    diff -u $_42SH_STDERR "$4"
}

for i in stdins/*[^~]
do
    do_one_test $i exit_statuses/$(basename $i) stdouts/$(basename $i) stderrs/$(basename $i)&
done

# Wait for all tests to be over before exiting
wait
