#include "types.h"
/* insmenu 0x004F1140 -- guarded triple: a fade setup, a four-way 1.0f colour
 * write and a placement, then the gp byte latch.  Same guard shape as
 * 004EFD20 -- `bnel $2, $0, <epilogue>` with `ld $31` in the delay slot,
 * so the body is the == 0 arm. */
extern s32 insmenu_InsectVsPwWatchPanelIsOpaque_4f1090(void);
extern const u8 D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
extern void func_290010(const void *a, s32 b, s32 c, s32 d);
extern void func_2905B0(const void *a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsPwWatchPanelFadeIn_4f1140(void)
{
    if (insmenu_InsectVsPwWatchPanelIsOpaque_4f1090() == 0) {
        func_290010(D_004FA180, 0x1F, 1, -1);
        func_2905B0(D_004FA180, 0x1F, 1.0f, 1.0f, 1.0f, 1.0f);
        func_290690(D_004FA180, 0x1F, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
