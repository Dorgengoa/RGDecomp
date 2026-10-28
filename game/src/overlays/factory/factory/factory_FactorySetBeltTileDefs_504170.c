/* rgp:protos */
#define RGP_SELF_factory_FactorySetBeltTileDefs_504170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504170 -- store one pointer pair. */

typedef struct Mod {
    u8    pad0[0xCC];
    void *fCC;
    void *fD0;
} Mod;

void factory_FactorySetBeltTileDefs_504170(Mod *o, void *a, void *b)
{
    o->fCC = a;
    o->fD0 = b;
}
