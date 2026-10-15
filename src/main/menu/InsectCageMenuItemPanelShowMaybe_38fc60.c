#include "types.h"

extern s32 GetMenuWidgetRoot_390d70(void);
extern void UiSetWidgetListVisible_28c120(s32, void *, s32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00463E28[];
extern u8 D_00463E30[];

void InsectCageMenuItemPanelShowMaybe_38fc60(s32 p0)
{
    s32 r0;

    r0 = GetMenuWidgetRoot_390d70();
    UiSetWidgetListVisible_28c120(r0, D_00463E28, (p0 != 0));
    UiSetWidgetListVisible_28c120(r0, D_00463E30, 0);
    if (p0 != 0) {
        UiSetWidgetAlpha_2907a0(r0, 0x227, 1.0f);
        return;
    }
    UiSetWidgetAlpha_2907a0(r0, 0x227, 0.0f);
}
