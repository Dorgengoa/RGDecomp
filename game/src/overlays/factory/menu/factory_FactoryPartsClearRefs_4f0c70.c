/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsClearRefs_4f0c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F0C70 -- clear one module's wiring. */

typedef struct Mod {
    u8 pad0[0x8C];
    void *f8C;
    void *f90;
    void *f94;
} Mod;

void factory_FactoryPartsClearRefs_4f0c70(Mod *o)
{
    o->f8C = 0;
    o->f90 = 0;
    o->f94 = 0;
}
