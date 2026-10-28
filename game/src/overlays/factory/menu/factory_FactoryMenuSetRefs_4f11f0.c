/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuSetRefs_4f11f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F11F0 -- wire one module to the four
 * shared objects the screen builder hands every module. */

typedef struct Mod {
    u8 pad0[0x64];
    void *f64;
    void *f68;
    void *f6C;
    void *f70;
} Mod;

void factory_FactoryMenuSetRefs_4f11f0(Mod *o, void *a, void *b, void *c, void *d)
{
    o->f64 = a;
    o->f68 = b;
    o->f6C = c;
    o->f70 = d;
}
