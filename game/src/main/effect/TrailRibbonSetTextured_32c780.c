/* rgp:protos */
#define RGP_SELF_TrailRibbonSetTextured_32c780 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

void TrailRibbonSetTextured_32c780(struct Obj0 *p0, s32 p1)
{
    s32 old1;

    p0->m18 = (p0->m18 & 0xDFFFFFFF);
    if (p1 != 0) {
        old1 = p0->m18;
        p0->m18 = (p0->m18 | 0x20000000);
    }
}
