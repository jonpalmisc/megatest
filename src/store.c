//===-- store.c - Store and product method implementations ----------------===//
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

#include "store.h"

#include <stdlib.h>

//===-- Product -----------------------------------------------------------===//

// Inspect for proper structure representation.
Product *ProductCreate(unsigned id, float price, unsigned stock) {
  Product *p = (Product *)malloc(sizeof(Product));

  p->id = id;
  p->price = price;
  p->stock = stock;

  return p;
}

//===-- Store -------------------------------------------------------------===//

// Inspect for proper structure representation.
Store *StoreCreate(unsigned productLimit) {
  Store *s = (Store *)malloc(sizeof(Store));

  s->name = "Untitled Store";
  s->products = 0;
  s->capacity = productLimit;
  s->inventory = (Product **)malloc(s->capacity * sizeof(Product *));

  return s;
}

// Inspect for proper structure representation.
void StoreInit(Store *s, unsigned productLimit) {
  s->name = "Untitled Store";
  s->products = 0;
  s->capacity = productLimit;
  s->inventory = (Product **)malloc(s->capacity * sizeof(Product *));
}

// Inspect for HLIL array detection and structure member access.
bool StoreAddProduct(Store *s, Product *p) {
  if (s->products >= s->capacity)
    return false;

  s->inventory[s->products++] = p;
  return true;
}

// Inspect for HLIL array detection and structure member access.
unsigned StoreTotalStock(Store *s) {
  unsigned total = 0;

  for (unsigned i = 0; i < s->products; i++)
    total += s->inventory[i]->stock;

  return total;
}

// Inspect for HLIL array detection and structure member access.
float StoreTotalValue(Store *s) {
  float total = 0;

  for (unsigned i = 0; i < s->products; i++)
    total += s->inventory[i]->price;

  return total;
}

// This should produce x87 floating point operations on x86.
long double StoreAverageValue(Store *s) {
  long double total = 0.0;

  for (unsigned i = 0; i < s->products; i++)
    total += (long double)s->inventory[i]->price;

  return total / (long double)s->products;
}

// Inspect for HLIL array detection.
void StoreFree(Store *s) {
  for (unsigned i = 0; i < s->products; i++)
    free(s->inventory[i]);

  free(s->inventory);
}
