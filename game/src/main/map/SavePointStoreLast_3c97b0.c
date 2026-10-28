/* rgp:protos */
#define RGP_SELF_SavePointStoreLast_3c97b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483894;

struct Obj0;

struct Obj0 {
    u8 pad000[0xF8];
    s16 mF8;
    u8 pad0FA[0x6];
    s64 m100;
};

s32 SavePointStoreLast_3c97b0(struct Obj0 *p0, s32 p1, s64 p2)
{
    s32 t0;
    s32 rv0;

    t0 = D_00483894;
    rv0 = 1;
    if (t0 == 0) {
        rv0 = 0;
    } else {
        p0->mF8 = p1;
        p0->m100 = p2;
        rv0 = 1;
    }
    return rv0;
}
