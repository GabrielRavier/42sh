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

do_one_test_direct_input_file()
{
    _42SH_STDOUT=`mktemp`
    _42SH_STDERR=`mktemp`

    $_42SH "$1" >"$_42SH_STDOUT" 2>"$_42SH_STDERR"
    _42SH_EXIT_STATUS=$?
    [ $_42SH_EXIT_STATUS == $(cat "$2") ] || echo "Incorrect exit status $_42SH_EXIT_STATUS for $1"
    diff -u "$_42SH_STDOUT" "$3"
    diff -u "$_42SH_STDERR" "$4"
}

test_setenv_print()
{
    diff -u <(echo setenv | some_var=some_val $_42SH | grep some_var) <(echo 'some_var=some_val')
    diff -u <(echo 'setenv | grep some_var' | some_var=some_val $_42SH) <(echo 'some_var=some_val')
}

test_sync_async()
{
    _42SH_STDOUT=`mktemp`

    diff -u <(echo '(sleep .1; echo second) & echo first; wait' | $_42SH 2>/dev/null | sed 's/ [0123456789]*$/ /') <(cat <<EOF
[1] 
first
second
EOF
                                                                                                   )
}

for i in stdins/*[^~]
do
    do_one_test $i exit_statuses/$(basename $i) stdouts/$(basename $i) stderrs/$(basename $i)&
done
wait

for i in stdins/*[^~]
do
    do_one_test_direct_input_file $i exit_statuses/$(basename $i) stdouts/$(basename $i) stderrs/$(basename $i)&
done
test_setenv_print&
test_sync_async&

# Wait for all tests to be over before exiting
wait
