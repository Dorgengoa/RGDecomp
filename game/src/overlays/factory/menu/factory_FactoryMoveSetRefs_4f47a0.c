/* rgp:protos */
#define RGP_SELF_factory_FactoryMoveSetRefs_4f47a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F47A0 -- wire one module and reset its flag. */

typedef struct Mod {
    u8    pad0[0x60];
    void *f60;
    void *f64;
    void *f68;
    void *f6C;
    u8    f70;
} Mod;

void factory_FactoryMoveSetRefs_4f47a0(Mod *o, void *a, void *b, void *c, void *d)
{
    o->f60 = a;
    o->f64 = b;
    o->f68 = c;
    o->f6C = d;
    o->f70 = 0;
}
