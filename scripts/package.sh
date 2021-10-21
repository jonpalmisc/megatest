#!/usr/bin/env sh

COMMIT=$(git rev-parse --short HEAD)

if [ ! -d "build" ]; then
  echo "Error: Cannot find build directory; run build.sh first."
  exit 1
fi

mkdir -p dist

cd build
zip ../dist/megatest_${COMMIT}.zip megatest_*
cd ../
