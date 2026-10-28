/* rgp:protos */
#define RGP_SELF_factory_FactorySetPartDefs_504180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504180 -- store one pointer pair. */

typedef struct Mod {
    u8    pad0[0xD4];
    void *fD4;
    void *fD8;
} Mod;

void factory_FactorySetPartDefs_504180(Mod *o, void *a, void *b)
{
    o->fD4 = a;
    o->fD8 = b;
}
