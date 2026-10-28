/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceClearRefs_4f7a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F7A20 -- clear one module's two pointer groups.
 *
 * ★ The store ORDER is 0x84/0x88/0x8C then 0x78/0x7C/0x80, i.e. the second
 * group is written first in ADDRESS terms and second in SOURCE terms; mwcc
 * emits gp-independent stores in source order here, so both groups are written
 * the way the reference lists them.
 */

typedef struct Mod {
    u8    pad0[0x78];
    void *f78;
    void *f7C;
    void *f80;
    void *f84;
    void *f88;
    void *f8C;
} Mod;

void factory_FactoryProduceClearRefs_4f7a20(Mod *o)
{
    o->f84 = 0;
    o->f88 = 0;
    o->f8C = 0;
    o->f78 = 0;
    o->f7C = 0;
    o->f80 = 0;
}
