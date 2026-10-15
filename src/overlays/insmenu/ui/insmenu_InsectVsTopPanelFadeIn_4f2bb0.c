#include "types.h"
/* insmenu 0x004F2BB0 -- the insmenu_FUN_004EFD20 guard shape.  The third
 * argument of func_290010 is `daddu $6, $5, $0` -- mwcc reuses the 1 already
 * materialised for $5 rather than re-materialising it, which is why this
 * function's mnemonic sequence does not hash into that family. */
extern s32 insmenu_InsectVsTopPanelIsOpaque_4f2b00(void);
extern const u8 D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
extern void func_290010(const void *a, s32 b, s32 c, s32 d);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsTopPanelFadeIn_4f2bb0(void)
{
    if (insmenu_InsectVsTopPanelIsOpaque_4f2b00() == 0) {
        func_290010(D_004FA180, 1, 1, -1);
        func_290690(D_004FA180, 1, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
