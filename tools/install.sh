#!/bin/bash

. tools/main.sh

sudo make install -C "$build_dir"

sudo chown -R $USER:$USER "$build_dir"
