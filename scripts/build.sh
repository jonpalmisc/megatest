#!/usr/bin/env sh

COMMIT=$(git rev-parse --short HEAD)

mkdir -p build && cd build

cmake -S ../ -B debug -DCMAKE_BUILD_TYPE=Debug
cmake -S ../ -B release -DCMAKE_BUILD_TYPE=Release
cmake --build debug
cmake --build release

mv debug/megatest megatest_${COMMIT}_debug
cp release/megatest megatest_${COMMIT}_stripped
mv release/megatest megatest_${COMMIT}

strip megatest_${COMMIT}_stripped

cd ../
