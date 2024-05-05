#!/bin/bash

for file in $(git ls-files | grep -E '^(include|src)/.*\.(c|cpp|h|hpp)$')
do
    echo 'Checking '$file
    clang-tidy --extra-arg=-std=c++$1 -p $2 --header-filter='^$' $file || exit 255
done
