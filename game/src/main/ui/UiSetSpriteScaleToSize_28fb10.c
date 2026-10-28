/* rgp:protos */
#define RGP_SELF_UiSetSpriteScaleToSize_28fb10 1
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
    u8 pad000[0xC];
    s16 m0C;
    s16 m0E;
    f32 m10;
    f32 m14;
};

struct Obj0 *UiSetSpriteScaleToSize_28fb10(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    struct Obj0 *r0;
    s16 t0;
    s16 t1;

    r0 = UiGetWidgetSprite_28fe10(p0, p1, p4);
    if (r0 != 0) {
        if (p2 != -0x270F) {
            t0 = r0->m0C;
            r0->m10 = (((f32)p2) / ((f32)t0));
        }
        if (p3 != -0x270F) {
            t1 = r0->m0E;
            r0->m14 = (((f32)p3) / ((f32)t1));
        }
    }
    return r0;
}
