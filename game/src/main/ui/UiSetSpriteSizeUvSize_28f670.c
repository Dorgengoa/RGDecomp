/* rgp:protos */
#define RGP_SELF_UiSetSpriteSizeUvSize_28f670 1
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
    u8 pad000[0x4];
    s16 m04;
    s16 m06;
    u8 pad008[0x4];
    s16 m0C;
    s16 m0E;
};

struct Obj0 *UiSetSpriteSizeUvSize_28f670(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    struct Obj0 *r0;

    r0 = UiGetWidgetSprite_28fe10(p0, p1, p6);
    if (r0 != 0) {
        if (p2 != -0x270F) {
            r0->m04 = p2;
        }
        if (p3 != -0x270F) {
            r0->m06 = p3;
        }
        if (p4 != -0x270F) {
            r0->m0C = p4;
        }
        if (p5 != -0x270F) {
            r0->m0E = p5;
        }
    }
    return r0;
}
