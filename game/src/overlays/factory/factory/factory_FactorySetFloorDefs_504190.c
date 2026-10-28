/* rgp:protos */
#define RGP_SELF_factory_FactorySetFloorDefs_504190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504190 -- store one pointer pair. */

typedef struct Mod {
    u8    pad0[0xC4];
    void *fC4;
    void *fC8;
} Mod;

void factory_FactorySetFloorDefs_504190(Mod *o, void *a, void *b)
{
    o->fC4 = a;
    o->fC8 = b;
}
