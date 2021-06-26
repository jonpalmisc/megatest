#!/usr/bin/env bash

# Re-create build directory tree
mkdir -p build
mkdir -p build/debug
mkdir -p build/release

# Perform debug build
cd build/debug
cmake ../../ -DCMAKE_BUILD_TYPE=Debug
make

# Rename to include "_debug" for clarity amongst others
mv megatest megatest_debug

# Perform release build
cd ../release
cmake ../../ -DCMAKE_BUILD_TYPE=Release
make

# Make a stripped copy of the release binary
cp megatest megatest_stripped
strip megatest_stripped

# Navigate back to source root
cd ../../
