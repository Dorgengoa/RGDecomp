#include "types.h"

extern s32 GetMenuWidgetRoot_390d70(void);
extern void MenuCursorBobToCell_2b3260(s32, s32, s32, s32);
extern s32 UiSelFrameAnimStep_28d820(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004DB430[];

s32 InsectCageMenuItemCursorBobCb_38f4a0(s32 p0)
{
    s32 r0;
    s32 r2;

    r0 = GetMenuWidgetRoot_390d70();
    MenuCursorBobToCell_2b3260(p0, r0, -0x12, 0x18);
    r2 = UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
