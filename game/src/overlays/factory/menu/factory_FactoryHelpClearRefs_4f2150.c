/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpClearRefs_4f2150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F2150 -- clear one module's wiring and its buffer. */

typedef struct Mod {
    u8    pad0[0x74];
    void *f74;
    u8    pad78[0x10];
    void *f88;
    void *f8C;
    void *f90;
} Mod;

void factory_FactoryHelpClearRefs_4f2150(Mod *o)
{
    o->f88 = 0;
    o->f8C = 0;
    o->f90 = 0;
    o->f74 = 0;
}
