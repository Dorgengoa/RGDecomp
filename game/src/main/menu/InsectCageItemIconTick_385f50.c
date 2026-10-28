/* rgp:protos */
#define RGP_SELF_InsectCageItemIconTick_385f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D84C;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    f32 m14;
    s32 m18;
};

void InsectCageItemIconTick_385f50(struct Obj0 *p0)
{
    s32 t0;
    f32 t1;
    f32 t2;
    f32 r0;
    s32 t3;

    t0 = p0->m10;
    if (t0 != 0) {
        t1 = p0->m14;
        t2 = D_0047D84C;
        r0 = WrapAngle_13c050((t2 + t1));
        p0->m14 = r0;
        t3 = p0->m18;
        p0->m18 = (t3 + -1);
        if ((t3 + -1) <= 0) {
            p0->m18 = 0;
        }
        return;
    }
}
