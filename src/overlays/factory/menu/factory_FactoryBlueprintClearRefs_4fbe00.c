#include "types.h"

/* factory.bin overlay, 0x004FBE00 -- clear one module's wiring. */

typedef struct Mod {
    u8 pad0[0x80];
    void *f80;
    void *f84;
    void *f88;
} Mod;

void factory_FactoryBlueprintClearRefs_4fbe00(Mod *o)
{
    o->f80 = 0;
    o->f84 = 0;
    o->f88 = 0;
}
