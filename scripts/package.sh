#!/usr/bin/env sh

COMMIT=$(git rev-parse --short HEAD)

mkdir -p dist

cd build
zip ../dist/megatest_${COMMIT}.zip megatest_*
cd ../
