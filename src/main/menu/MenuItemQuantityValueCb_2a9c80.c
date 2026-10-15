#include "types.h"

extern s32 UiSetWidgetSubItemValue_291250(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482360;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s32 MenuItemQuantityValueCb_2a9c80(struct Obj0 *p0)
{
    s32 r0;

    if (p0->m10 <= 0) {
        p0->m10 = 1;
    }
    r0 = UiSetWidgetSubItemValue_291250(D_00482360, 0x8C, 0, p0->m10);
    return 1;
}
