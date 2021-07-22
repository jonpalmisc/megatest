#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _STR(x) #x
#define STR(x) _STR(x)

/**
 * Compiler name and version
 */
#ifdef _MSC_VER
#define MT_COMPILER_NAME "MSVC"
#define MT_COMPILER_VERSION STR(_MSC_VER)
#elif defined(__clang__)
#define MT_COMPILER_NAME "Clang"
#define MT_COMPILER_VERSION STR(__clang_major__) \
"." STR(__clang_minor__)
#elif defined(__GNUC__)
#define MT_COMPILER_NAME "GCC"
#define MT_COMPILER_VERSION STR(__GNUC__) \
"." STR(__GNUC_MINOR__)
#else
#define MT_COMPILER_NAME "Unknown"
#define MT_COMPILER_VERSION ""
#endif

/**
 * Operating system
 */
#ifdef __linux__
#define MT_SYSTEM_NAME "Linux"
#elif defined(__APPLE__)
#define MT_SYSTEM_NAME "macOS"
#elif defined(_WIN32)
#define MT_SYSTEM_NAME "Windows"
#else
#define MT_SYSTEM_NAME "Unknown"
#endif

/**
 * Processor architecture
 */
#ifdef __i386__
#define MT_SYSTEM_ARCH "x86"
#elif defined(__x86_64__)
#define MT_SYSTEM_ARCH "x86_64"
#elif defined(__arm__)
#define MT_SYSTEM_ARCH "ARM"
#else
#define MT_SYSTEM_ARCH "Unknown"
#endif

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

#define Echo(s) printf("%s\n", s)

void PrintHeader()
{
    Echo("MEGATEST - Disassembler test binary");
    Echo("----------------------------------------------------------------------------\n");
    Echo("      Date:  " __DATE__ " " __TIME__);
    Echo("  Compiler:  " MT_COMPILER_NAME " " MT_COMPILER_VERSION);
    Echo("    System:  " MT_SYSTEM_NAME " " MT_SYSTEM_ARCH);
    Echo("\n----------------------------------------------------------------------------");
    Echo("Hint: This binary is meant to be viewed in a disassembler; it has no output.\n");
}

int main(int argc, char* argv[])
{
    PrintHeader();

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
        Echo("Today's random number was 1.");
        break;
    case 2:
        Echo("Today's random number was 2.");
        break;
    case 3:
        Echo("Today's random number was 3.");
        break;
    case 7:
        Echo("Today's random number was 7.");
        break;
    case 8:
        Echo("Today's random number was 8.");
        break;
    case 13:
        Echo("Today's random number was 13.");
        break;
    case 14:
        Echo("Today's random number was 14.");
        break;
    default:
        break;
    }

    return totalStock;
}
