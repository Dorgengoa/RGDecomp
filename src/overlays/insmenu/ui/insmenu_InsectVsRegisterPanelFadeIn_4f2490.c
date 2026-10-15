#include "types.h"
/* insmenu 0x004F2490 -- guarded pair of calls plus a gp byte latch.
 * Same guard shape as 004EE770: `bnel $2, $0, <epilogue>` with
 * `ld $31` in the delay slot, so the body is the == 0 arm. */
extern s32 insmenu_InsectVsRegisterPanelIsOpaque_4f23e0(void);
extern const u8 D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
extern void func_290010(const void *a, s32 b, s32 c, s32 d);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsRegisterPanelFadeIn_4f2490(void)
{
    if (insmenu_InsectVsRegisterPanelIsOpaque_4f23e0() == 0) {
        func_290010(D_004FA180, 0x15, 1, -1);
        func_290690(D_004FA180, 0x15, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
