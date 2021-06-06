#!/usr/bin/env bash

# Re-create build directory tree
rm -fr build
mkdir build
mkdir build/debug
mkdir build/release

# Perform debug build
cd build/debug
cmake ../../ -DCMAKE_BUILD_TYPE=Debug
make

# Perform release build
cd ../release
cmake ../../ -DCMAKE_BUILD_TYPE=Release
make

# Make a stripped copy of the release binary
cp megatest megatest_stripped
strip megatest_stripped

# Navigate back to source root
cd ../../
