/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialClearRefs_4f3fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F3FC0 -- clear one module's wiring and cursor.
 *
 * ★ `addiu $3, $0, -0x1` is hoisted to the SECOND instruction, before the two
 * stores that use it: mwcc materialises the shared -1 once and the scheduler
 * fills the load-delay shadow with it.  Nothing in the source forces that.
 */

typedef struct Mod {
    void *f0;
    s16   f4;
    s16   f6;
    s16   f8;
    s16   fA;
    s16   fC;
    u8    padE[0x11];
    u8    f1F;
    u8    pad20[0x20];
    void *f40;
    void *f44;
    void *f48;
    void *f4C;
} Mod;

void factory_FactoryMaterialClearRefs_4f3fc0(Mod *o)
{
    o->f40 = 0;
    o->f44 = 0;
    o->f48 = 0;
    o->f4C = 0;
    o->f0 = 0;
    o->f4 = 0;
    o->f6 = -1;
    o->f8 = -1;
    o->fC = 0;
    o->fA = 0;
    o->f1F = 0;
}
