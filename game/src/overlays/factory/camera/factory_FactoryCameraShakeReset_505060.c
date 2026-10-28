/* rgp:protos */
#define RGP_SELF_factory_FactoryCameraShakeReset_505060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00505060 -- clear one module's wiring. */

typedef struct Mod {
    u8    pad0[0x3E8];
    void *f3E8;
    void *f3EC;
    void *f3F0;
} Mod;

void factory_FactoryCameraShakeReset_505060(Mod *o)
{
    o->f3E8 = 0;
    o->f3EC = 0;
    o->f3F0 = 0;
}
