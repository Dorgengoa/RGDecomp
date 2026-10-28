/* rgp:protos */
#define RGP_SELF_MenuWinFadeColorToInt_26c1c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA0];
    f32 mA0;
    f32 mA4;
    f32 mA8;
    f32 mAC;
    u8 pad0B0[0x4];
    s32 mB4;
};

f32 MenuWinFadeColorToInt_26c1c0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    p0->mA0 = ((f32)p1);
    p0->mA4 = ((f32)p2);
    p0->mA8 = ((f32)p3);
    p0->mAC = ((f32)p4);
    p0->mB4 = p5;
    return ((f32)p4);
}
