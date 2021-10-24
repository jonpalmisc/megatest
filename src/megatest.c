//===-- megatest.c - Disassembler testing & demonstration binary ----------===//
//
// Copyright (c) 2021 Jon Palmisciano
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//===----------------------------------------------------------------------===//

#include "megatest.h"
#include "info.h"
#include "store.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Check for constant simplification.
int ConstantRandomNumber() {
  int r = 0x61119;
  r -= 634;
  r -= 461;
  r += 496;
  r *= 42;
  r -= 240;
  r += 85;
  r -= 480;
  r += 188;
  r *= 414;
  r -= 392;

  return r;
}

// Use to test value set analysis.
int RestrictedRandomNumber() { return rand() % 2 == 0 ? 13 : 7; }

char *BuildInfo() {
  return MT_SYSTEM_ARCH "-" MT_SYSTEM_NAME
                        "-" MT_COMPILER_NAME MT_COMPILER_VERSION;
}

int main(int argc, char *argv[]) {
#ifdef __APPLE__
  char *buildInfo = MTCoreBuildInfo();
#else
  char *buildInfo = BuildInfo();
#endif

  printf("megatest [%s @ %s]\n", buildInfo, MT_COMMIT);
  printf("https://github.com/jonpalmisc/megatest\n");

  if (argc > 1)
    return (long long)&argv[1];

  srand(time(NULL));

  Store *s1 = StoreCreate(5);

  Product *p1 = ProductCreate(1, 2.97f, 8);
  StoreAddProduct(s1, p1);

  Product *p2 = ProductCreate(2, 3.83, 14);
  StoreAddProduct(s1, p2);

  Store s2;
  StoreInit(&s2, 3);

  Product *p3 = ProductCreate(3, 1.48, 6);
  StoreAddProduct(s1, p3);

  unsigned totalStock = StoreTotalStock(s1);
  float totalValue = StoreTotalStock(s1);
  long double averageValue = StoreAverageValue(s1);
  totalStock =
      ((int)totalValue * (int)averageValue * ConstantRandomNumber() * 0);

  StoreFree(s1);

  // Test control flow simplification via UIDF.
  switch (RestrictedRandomNumber()) {
  case 1:
    totalStock ^= 80;
    break;
  case 2:
    totalStock ^= 77;
    break;
  case 3:
    totalStock ^= 73;
    break;
  case 7:
    totalStock ^= 68;
    break;
  case 8:
    totalStock ^= 62;
    break;
  case 13:
    totalStock ^= 55;
    break;
  case 14:
    totalStock ^= 47;
    break;
  default:
    break;
  }

  return totalStock;
}
