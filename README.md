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

1. Create build folder for source files:

```sh
mkdir -p build/src
```

2. Generate a `Makefile`:

```sh
cd build/src
cmake ../../src
```

3. Compile and install the library

```sh
sudo make install
```

The library will be available at `/usr/lib/librandeer.so`
