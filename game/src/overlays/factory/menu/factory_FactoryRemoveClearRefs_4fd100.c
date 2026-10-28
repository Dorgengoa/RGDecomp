/* rgp:protos */
#define RGP_SELF_factory_FactoryRemoveClearRefs_4fd100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FD100 -- clear one module's wiring. */

typedef struct Mod {
    u8 pad0[0x68];
    void *f68;
    void *f6C;
    void *f70;
} Mod;

void factory_FactoryRemoveClearRefs_4fd100(Mod *o)
{
    o->f68 = 0;
    o->f6C = 0;
    o->f70 = 0;
}
