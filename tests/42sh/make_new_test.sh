#!/usr/bin/env bash
# Pass the name of the new test to this script and it will generate files for it

# Execute this from the directory that which contains the script
cd "$(dirname "$0")"

[ -z "$1" ] && exit 1
touch stdins/$1
touch stdouts/$1
touch stderrs/$1
echo 0 >exit_statuses/$1
