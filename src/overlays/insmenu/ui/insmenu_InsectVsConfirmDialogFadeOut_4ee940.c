#include "types.h"
/* insmenu 0x004EE940 -- the 004EE770 shape with a 0.0f first float, so the
 * literal is `mtc1 $0, $f12` and the lui disappears: 17 words, not 18. */
extern s32 insmenu_InsectVsConfirmDialogIsHidden_4ee8a0(void);
extern const u8 D_004FA180[];
extern f32 D_0047D49C;
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsConfirmDialogFadeOut_4ee940(void)
{
    if (insmenu_InsectVsConfirmDialogIsHidden_4ee8a0() == 0) {
        func_290690(D_004FA180, 6, 0.0f, D_0047D49C, -1.0f);
    }
}
