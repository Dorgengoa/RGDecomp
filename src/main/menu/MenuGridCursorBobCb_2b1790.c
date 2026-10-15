#include "types.h"

extern void MenuCursorBobToCell_2b3260(s32, s32, s32, s32);
extern s32 UiSelFrameAnimStep_28d820(void *, s32);
extern void MenuWidgetPulseColor_2b3200(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004823CC;
extern u8 D_004DB430[];

s32 MenuGridCursorBobCb_2b1790(s32 p0, s32 p1)
{
    s32 r1;
    u8 t0;

    MenuCursorBobToCell_2b3260(p0, p1, -0xE, 0x1C);
    r1 = UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    t0 = D_004823CC;
    if (t0 != 0) {
        MenuWidgetPulseColor_2b3200();
    }
    return 1;
}
