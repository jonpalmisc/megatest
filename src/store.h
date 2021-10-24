//===-- store.h - Store and product structure definitions -----------------===//
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

#pragma once

#include <stdbool.h>

//===-- Product -----------------------------------------------------------===//

/**
 * A product in an inventory.
 */
typedef struct {
  unsigned id;
  float price;
  unsigned stock;
} Product;

/**
 * Allocate and initialize a new Product instance.
 */
Product *ProductCreate(unsigned id, float price, unsigned stock);

//===-- Store -------------------------------------------------------------===//

/**
 * A store with an inventory of products.
 */
typedef struct {
  char *name;
  unsigned products;
  unsigned capacity;
  Product **inventory;
} Store;

/**
 * Allocate and initialize a new Store instance.
 */
Store *StoreCreate(unsigned productLimit);

/**
 * Initialize an already-allocated Store instance.
 */
void StoreInit(Store *s, unsigned productLimit);

/**
 * Add a product to the store's inventory.
 */
bool StoreAddProduct(Store *s, Product *p);

/**
 * Calculate the total stock of the store.
 */
unsigned StoreTotalStock(Store *s);

/**
 * Calculate the total value of the store.
 */
float StoreTotalValue(Store *s);

/**
 * Calculate the average value of the store.
 */
long double StoreAverageValue(Store *s);

/**
 * Free all of the products in the store.
 */
void StoreFree(Store *s);
