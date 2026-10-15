#include "types.h"

/* factory.bin overlay, 0x004F0C50 -- wire one module to the four
 * shared objects the screen builder hands every module. */

typedef struct Mod {
    u8 pad0[0x8C];
    void *f8C;
    void *f90;
    void *f94;
    void *f98;
} Mod;

void factory_FactoryPartsSetRefs_4f0c50(Mod *o, void *a, void *b, void *c, void *d)
{
    o->f8C = a;
    o->f90 = b;
    o->f94 = c;
    o->f98 = d;
}
