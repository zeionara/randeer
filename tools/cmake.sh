#!/bin/bash

. tools/main.sh

cmake -B "$build_dir"
ln -f "$build_dir/compile_commands.json"
