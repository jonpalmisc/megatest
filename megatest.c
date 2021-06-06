#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    unsigned products;
    unsigned capacity;
    Product** inventory;
} Store;

/**
 * Allocate and initialize a new Store instance
 * Hint: Inspect for proper structure representation.
 */
Store* StoreCreate(unsigned int productLimit)
{
    Store* s = (Store*)malloc(sizeof(Store));

    s->products = 0;
    s->capacity = productLimit;
    s->inventory = (Product**)malloc(s->capacity * sizeof(Product*));

    return s;
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
long double StoreAverageValue(Store *s)
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
int RandomNumberTM()
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

#define Echo(s) printf("%s\n", s)

void PrintHeader()
{
    Echo("MEGATEST - Disassembler test binary");
    Echo("----------------------------------------------------------------------------");
    Echo("Hint: This binary is meant to be viewed in a disassembler; it has no output.");
}

int main(int argc, char* argv[])
{
    PrintHeader();

    if (argc > 1)
        return (long long)&argv[1];

    Store* s = StoreCreate(5);

    Product* p1 = ProductCreate(1, 2.97f, 8);
    StoreAddProduct(s, p1);

    Product* p2 = ProductCreate(2, 3.83, 14);
    StoreAddProduct(s, p2);

    Product* p3 = ProductCreate(3, 1.48, 6);
    StoreAddProduct(s, p3);

    unsigned totalStock = StoreTotalStock(s);
    float totalValue = StoreTotalStock(s);
    long double averageValue = StoreAverageValue(s);
    totalStock = ((int)totalValue * (int)averageValue * RandomNumberTM() * 0);

    StoreFree(s);

    return totalStock;
}
