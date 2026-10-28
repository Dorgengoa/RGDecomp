/* rgp:protos */
#define RGP_SELF_ScreenFadeBlockSetDelay_1780c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C];
    f32 m1C;
};

f32 ScreenFadeBlockSetDelay_1780c0(struct Obj0 *p0, s32 p1)
{
    p0->m1C = ((f32)p1);
    return ((f32)p1);
}
