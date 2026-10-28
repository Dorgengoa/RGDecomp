/* rgp:protos */
#define RGP_SELF_GsPktSetPrimType_13f470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x70];
    u8 m70;
    u8 pad071[0x9F];
    s32 m110;
    s32 m114;
};

void GsPktSetPrimType_13f470(struct Obj0 *p0, s32 p1)
{
    u8 t0;

    p0->m114 = 0;
    t0 = p0->m70;
    p0->m70 = ((t0 & -8) | (p1 & 7));
    p0->m110 = 0x3F800000;
    GsPktBeginPrimAD_13f6b0(p0);
}
