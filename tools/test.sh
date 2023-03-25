#!/bin/bash

build_dir=build/src  # TODO: change to just "build"

sudo make -C "$build_dir" && ctest --test-dir "$build_dir"
