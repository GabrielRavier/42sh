#!/usr/bin/env bash

# Execute tests from the directory that which contains the script
cd "$(dirname "$0")"

MYSH=$(realpath ../../42sh)

do_one_test()
{
    MYSH_STDOUT=`mktemp`
    MYSH_STDERR=`mktemp`

    $MYSH <"$1" >$MYSH_STDOUT 2>$MYSH_STDERR
    MYSH_EXIT_STATUS=$?
    [ $MYSH_EXIT_STATUS == $(cat "$2") ] || echo "Incorrect exit status $MYSH_EXIT_STATUS for $1"
    diff -u $MYSH_STDOUT "$3"
    diff -u $MYSH_STDERR "$4"
}

for i in stdins/*[^~]
do
    do_one_test $i exit_statuses/$(basename $i) stdouts/$(basename $i) stderrs/$(basename $i)
done

# Wait for all tests to be over before exiting
wait
