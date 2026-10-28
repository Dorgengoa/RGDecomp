/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialSetRefs_4f3f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F3F60 -- wire one module, skipping null arguments,
 * then tail-call its reset.
 *
 * ★ Each guard is a PLAIN `beqz` with a `nop` delay slot and the store is the
 * FALL-THROUGH, so the source condition is the positive `!= 0` one.
 * ★ mwcc -O4 emits the closing call as a real tail call (`j`), which is the
 * shape the overlay track already measured on insmenu.
 */

typedef struct Mod {
    u8    pad0[0x40];
    void *f40;
    void *f44;
    void *f48;
    void *f4C;
} Mod;

/*rgp*/

void factory_FactoryMaterialSetRefs_4f3f60(Mod *o, void *a, void *b, void *c, void *d)
{
    if (a != 0) {
        o->f40 = a;
    }
    if (b != 0) {
        o->f44 = b;
    }
    if (c != 0) {
        o->f48 = c;
    }
    if (d != 0) {
        o->f4C = d;
    }
    factory_FactoryMaterialFrameInit_4f3d80(o);
}
