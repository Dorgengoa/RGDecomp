#include "types.h"
/* insmenu 0x004F0630 -- guarded pair of calls plus a gp byte latch.
 * Same guard shape as 004EE770: `bnel $2, $0, <epilogue>` with
 * `ld $31` in the delay slot, so the body is the == 0 arm. */
extern s32 insmenu_InsectVsRegPwPanelIsOpaque_4f0580(void);
extern const u8 D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
extern void func_290010(const void *a, s32 b, s32 c, s32 d);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsRegPwPanelFadeIn_4f0630(void)
{
    if (insmenu_InsectVsRegPwPanelIsOpaque_4f0580() == 0) {
        func_290010(D_004FA180, 0x4C, 1, -1);
        func_290690(D_004FA180, 0x4C, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
