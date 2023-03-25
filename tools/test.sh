#!/bin/bash

. tools/main.sh

sudo make -C "$build_dir" && ctest --test-dir "$build_dir"
