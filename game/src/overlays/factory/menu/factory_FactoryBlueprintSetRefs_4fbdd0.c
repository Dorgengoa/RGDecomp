/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintSetRefs_4fbdd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FBDD0 -- wire one module and reset its state. */

typedef struct Mod {
    u8    pad0[0x6C];
    u8    f6C;
    u8    f6D;
    u8    pad6E[2];
    void *f70;
    u8    pad74[0xC];
    void *f80;
    void *f84;
    void *f88;
    void *f8C;
    u8    f90;
} Mod;

void factory_FactoryBlueprintSetRefs_4fbdd0(Mod *o, void *a, void *b, void *c, void *d)
{
    o->f80 = a;
    o->f84 = b;
    o->f88 = c;
    o->f8C = d;
    o->f90 = 0;
    o->f70 = 0;
    o->f6C = 0;
    o->f6D = 0;
}
