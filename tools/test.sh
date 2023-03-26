#!/bin/bash

. tools/main.sh

make -C "$build_dir" && ctest --test-dir "$build_dir"
echo -e '\n================ Test results =================\n'
cat ./build/Testing/Temporary/LastTest.log
