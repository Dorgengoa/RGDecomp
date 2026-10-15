#include "types.h"

extern void * UiGetWidgetSprite_28fe10(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
};

struct Obj0 *UiSetSpriteU_28f930(s32 p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj0 *r0;

    r0 = UiGetWidgetSprite_28fe10(p0, p1, p3);
    if (r0 != 0) {
        if (p2 != -0x270F) {
            r0->m08 = p2;
        }
    }
    return r0;
}
