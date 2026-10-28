/* rgp:protos */
#define RGP_SELF_factory_FactoryRemoveSetRefs_4fd0e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FD0E0 -- wire one module to the four
 * shared objects the screen builder hands every module. */

typedef struct Mod {
    u8 pad0[0x68];
    void *f68;
    void *f6C;
    void *f70;
    void *f74;
} Mod;

void factory_FactoryRemoveSetRefs_4fd0e0(Mod *o, void *a, void *b, void *c, void *d)
{
    o->f68 = a;
    o->f6C = b;
    o->f70 = c;
    o->f74 = d;
}
