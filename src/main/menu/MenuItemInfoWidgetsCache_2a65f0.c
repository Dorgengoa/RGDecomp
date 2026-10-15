#include "types.h"

extern void memset(void *, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern s32 UiGetWidgetText_28f620(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482360;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
};

s32 MenuItemInfoWidgetsCache_2a65f0(struct Obj0 *p0)
{
    s32 t0;
    s32 r1;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 r3;
    s32 t3;
    s32 r4;

    memset(p0, 0, 0x10);
    t0 = D_00482360;
    r1 = UiGetWidgetSprite_28fe10(t0, 0x231, 0);
    p0->m00 = r1;
    t1 = D_00482360;
    r2 = UiGetWidgetSprite_28fe10(t1, 0x230, 0);
    p0->m04 = r2;
    t2 = D_00482360;
    r3 = UiGetWidgetText_28f620(t2, 0x230, 0);
    p0->m08 = r3;
    t3 = D_00482360;
    r4 = UiGetWidgetSprite_28fe10(t3, 0x232, 0);
    p0->m0C = r4;
    return 1;
}
