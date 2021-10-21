//===-- megatest.c - Disassembler testing & demonstration binary ----------===//
//
// MEGATEST is a small test binary that is useful for demonstrating existing
// disassembler features and serving as a test case while developing new ones.
//
//===----------------------------------------------------------------------===//
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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// I probably found this on Stack Overflow; I don't completely remember why it
// is relevant or needed, but here it is.
#define _STR(x) #x
#define STR(x) _STR(x)

//===-- Preprocessor abuse ------------------------------------------------===//

/* Build commit */
#ifndef MT_COMMIT
#define MT_COMMIT "0000000"
#endif

/* Compiler name & version */
#ifdef _MSC_VER
#define MT_COMPILER_NAME "msvc"
#define MT_COMPILER_VERSION STR(_MSC_VER)
#elif defined(__clang__)
#define MT_COMPILER_NAME "clang"
#define MT_COMPILER_VERSION STR(__clang_major__)
#elif defined(__GNUC__)
#define MT_COMPILER_NAME "gcc"
#define MT_COMPILER_VERSION STR(__GNUC__)
#else
#define MT_COMPILER_NAME "other"
#define MT_COMPILER_VERSION ""
#endif

/* Target platform */
#ifdef __linux__
#define MT_SYSTEM_NAME "linux"
#elif defined(__APPLE__)
#define MT_SYSTEM_NAME "mac"
#elif defined(_WIN32)
#define MT_SYSTEM_NAME "win"
#else
#define MT_SYSTEM_NAME "other"
#endif

/* Target architecture */
#ifdef __i386__
#define MT_SYSTEM_ARCH "x86"
#elif defined(__x86_64__)
#define MT_SYSTEM_ARCH "x86_64"
#elif defined(__aarch64__)
#define MT_SYSTEM_ARCH "arm64"
#elif defined(__arm__)
#define MT_SYSTEM_ARCH "arm"
#else
#define MT_SYSTEM_ARCH "other"
#endif

//===-- Core program ------------------------------------------------------===//

typedef struct {
    unsigned id;
    float price;
    unsigned stock;
} Product;

/**
 * Allocate and initialize a new Product instance.
 * Hint: Inspect for proper structure representation.
 */
Product* ProductCreate(unsigned id, float price, unsigned stock)
{
    Product* p = (Product*)malloc(sizeof(Product));

    p->id = id;
    p->price = price;
    p->stock = stock;

    return p;
}

typedef struct {
    char* name;
    unsigned products;
    unsigned capacity;
    Product** inventory;
} Store;

/**
 * Allocate and initialize a new Store instance.
 * Hint: Inspect for proper structure representation.
 */
Store* StoreCreate(unsigned productLimit)
{
    Store* s = (Store*)malloc(sizeof(Store));

    s->name = "Untitled Store";
    s->products = 0;
    s->capacity = productLimit;
    s->inventory = (Product**)malloc(s->capacity * sizeof(Product*));

    return s;
}

/**
 * Initialize an already-allocated Store instance.
 * Hint: Inspect for proper structure representation.
 */
void StoreInit(Store* s, unsigned productLimit)
{
    s->name = "Untitled Store";
    s->products = 0;
    s->capacity = productLimit;
    s->inventory = (Product**)malloc(s->capacity * sizeof(Product*));
}

/**
 * Add a product to the store's inventory.
 * Hint: Inspect for HLIL array detection and structure member access.
 */
bool StoreAddProduct(Store* s, Product* p)
{
    if (s->products >= s->capacity)
        return false;

    s->inventory[s->products++] = p;
    return true;
}

/**
 * Calculate the total stock of the store.
 * Hint: Inspect for HLIL array detection and structure member access.
 */
unsigned StoreTotalStock(Store* s)
{
    unsigned total = 0;

    for (unsigned i = 0; i < s->products; i++)
        total += s->inventory[i]->stock;

    return total;
}

/**
 * Calculate the total value of the store.
 * Hint: Inspect for HLIL array detection and structure member access.
 */
float StoreTotalValue(Store* s)
{
    float total = 0;

    for (unsigned i = 0; i < s->products; i++)
        total += s->inventory[i]->price;

    return total;
}

/**
 * Calculate the average value of the store.
 * Hint: This should produce x87 floating point operations on x86.
 */
long double StoreAverageValue(Store* s)
{
    long double total = 0.0;

    for (unsigned i = 0; i < s->products; i++)
        total += (long double)s->inventory[i]->price;

    return total / (long double)s->products;
}

/**
 * Free all of the products in the store.
 * Hint: Inspect for HLIL array detection.
 */
void StoreFree(Store* s)
{
    for (unsigned i = 0; i < s->products; i++)
        free(s->inventory[i]);

    free(s->inventory);
}

/**
 * Get a "random" number.
 * Hint: Check for constant simplification.
 */
int ConstantRandomNumber()
{
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

/**
 * Get a "random" number.
 * Hint: Use to test value set analysis.
 */
int RestrictedRandomNumber()
{
    return rand() % 2 == 0 ? 13 : 7;
}

int main(int argc, char* argv[])
{
    printf("megatest [%s-%s-%s%s @ %s]\n", MT_SYSTEM_ARCH, MT_SYSTEM_NAME, MT_COMPILER_NAME, MT_COMPILER_VERSION, MT_COMMIT);
    printf("https://github.com/jonpalmisc/megatest\n");

    if (argc > 1)
        return (long long)&argv[1];

    srand(time(NULL));

    Store* s1 = StoreCreate(5);

    Product* p1 = ProductCreate(1, 2.97f, 8);
    StoreAddProduct(s1, p1);

    Product* p2 = ProductCreate(2, 3.83, 14);
    StoreAddProduct(s1, p2);

    Store s2;
    StoreInit(&s2, 3);

    Product* p3 = ProductCreate(3, 1.48, 6);
    StoreAddProduct(s1, p3);

    unsigned totalStock = StoreTotalStock(s1);
    float totalValue = StoreTotalStock(s1);
    long double averageValue = StoreAverageValue(s1);
    totalStock = ((int)totalValue * (int)averageValue * ConstantRandomNumber() * 0);

    StoreFree(s1);

    // Test control flow simplification via UIDF.
    switch (RestrictedRandomNumber()) {
    case 1:
        puts("Today's random number was 1.");
        break;
    case 2:
        puts("Today's random number was 2.");
        break;
    case 3:
        puts("Today's random number was 3.");
        break;
    case 7:
        puts("Today's random number was 7.");
        break;
    case 8:
        puts("Today's random number was 8.");
        break;
    case 13:
        puts("Today's random number was 13.");
        break;
    case 14:
        puts("Today's random number was 14.");
        break;
    default:
        break;
    }

    return totalStock;
}
