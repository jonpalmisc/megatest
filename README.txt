MEGATEST: Disassembler test & demonstration binary                        v0.5.1
________________________________________________________________________________

ABOUT

  MEGATEST is a small program I've written for the purpose of testing basic
  disassembler features, comparing decompiler output, etc.

BUILD

  For a basic build, just clone the repository, then just run CMake and build:

    $ git clone git@github.com:jonpalmisc/megatest.git && cd megatest
    $ cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug # ...
    $ cmake --build build

  If you would prefer to quickly build debug, release, and stripped binaries all
  at once, you can use the included script:

    $ ./scripts/make.sh

LICENSE

  Copyright (c) 2021 Jon Palmisciano, licensed under the BSD-3-Clause License.
