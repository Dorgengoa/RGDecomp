/* rgp:protos */
#define RGP_SELF_GsPktOpenPrim_13f730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x6C];
    u8 m70;
    u8 pad071[0x77];
    s32 mE8;
    u8 pad0EC[0x24];
    s32 m110;
};

void GsPktOpenPrim_13f730(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    u8 t1;

    p0->mE8 = 1;
    t0 = p0->m00;
    if (t0 != 0) {
        p0->mE8 = 0;
        t1 = p0->m70;
        p0->m70 = ((t1 & -8) | (p1 & 7));
        p0->m110 = 0x3F800000;
        GsPktOpen_13f4a0(p0);
        GsPktBeginPrimAD_13f6b0(p0);
    }
}
