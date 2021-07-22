MEGATEST: Disassembler test binary                                        v0.3.0
________________________________________________________________________________

ABOUT

  MEGATEST is a small program I've written for the purpose of testing basic
  disassembler features, comparing decompiler output, etc.

BUILD

  Clone the repository, then just run CMake and build:

    $ mkdir build && cd build
    $ cmake ../
    $ make

  Additionally, you may want to use the -DCMAKE_BUILD_TYPE option to adjust the
  amount of optimization, etc. If you would prefer to quickly build debug,
  release, and stripped binaries all at once, you can use the included scripts:

    $ ./clean.sh
    $ ./make.sh

LICENSE

  Public Domain - See LICENSE.txt for more details.
