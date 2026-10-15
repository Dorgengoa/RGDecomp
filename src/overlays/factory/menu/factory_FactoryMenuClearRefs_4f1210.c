#include "types.h"

/* factory.bin overlay, 0x004F1210 -- clear one module's wiring. */

typedef struct Mod {
    u8 pad0[0x64];
    void *f64;
    void *f68;
    void *f6C;
} Mod;

void factory_FactoryMenuClearRefs_4f1210(Mod *o)
{
    o->f64 = 0;
    o->f68 = 0;
    o->f6C = 0;
}
