#include "types.h"

/* factory.bin overlay, 0x004F47C0 -- clear one module's wiring. */

typedef struct Mod {
    u8 pad0[0x60];
    void *f60;
    void *f64;
    void *f68;
} Mod;

void factory_FactoryMoveClearRefs_4f47c0(Mod *o)
{
    o->f60 = 0;
    o->f64 = 0;
    o->f68 = 0;
}
