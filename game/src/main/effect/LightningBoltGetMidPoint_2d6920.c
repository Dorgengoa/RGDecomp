/* rgp:protos */
#define RGP_SELF_LightningBoltGetMidPoint_2d6920 1
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
    u8 pad000[0xC2];
    s16 mC2;
};

s32 LightningBoltGetMidPoint_2d6920(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s32 rv1;
    s32 r0;

    t0 = p0->mC2;
    rv1 = 1;
    if (t0 <= 0) {
        rv1 = 0;
    } else {
        r0 = ((s32)sceVu0CopyVector(p1, (struct Obj0 *)((u8 *)p0 + 0x40)));
        rv1 = 1;
    }
    return rv1;
}
