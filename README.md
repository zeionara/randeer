# randeer

<p align="center">
    <img src="assets/images/logo.png"/>
</p>

A simple randomization library

## Prerequisites

If you don't have `cmake` installed, install it using the following command:

```sh
sudo apt-get update && sudo apt-get install cmake
```

## Build

1. Generate a `Makefile`:

```sh
cmake -B build/src
```

2. Compile and install the library

```sh
sudo make install -C build/src
```

The library will be available at `/usr/lib/librandeer.so`

## Test

After building the project, tests can be run using the following command:

```sh
ctest --test-dir build/src
```

To recompile the project and run tests use the following command:

```sh
./tools/test.sh
```
