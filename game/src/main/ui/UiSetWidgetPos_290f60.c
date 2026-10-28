/* rgp:protos */
#define RGP_SELF_UiSetWidgetPos_290f60 1
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
    u8 pad000[0x14];
    f32 m14;
    f32 m18;
    u8 pad01C[0x44];
    f32 m60;
    f32 m64;
};

struct Obj0 *UiSetWidgetPos_290f60(s32 p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj0 *r0;

    r0 = UiFindWidget_290460(p0, p1);
    if (r0 != 0) {
        r0->m14 = ((f32)p2);
        r0->m18 = ((f32)p3);
        r0->m60 = ((f32)p2);
        r0->m64 = ((f32)p3);
    }
    return r0;
}
