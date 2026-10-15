#include "types.h"
/* insmenu 0x004F1930 (pass-27 window) -- one of seven identical members.
 * The guard is `bnel $2, $0, <epilogue>` with `ld $31` in the delay
 * slot, so the body is the FALL-THROUGH and the source condition is
 * `== 0`.  The five-argument call is the matched insmenu_InsectVsBackGuideHide_4ea000
 * verbatim: D_0047D3E0 is gp - 0x7D90, inside the gp window, so it is
 * NOT const, and the 0.0f / -1.0f are inline literals. */
extern const u8 D_004FA180[];
extern f32 D_0047D3E0;
extern s32 insmenu_InsectVsTwoPlayerCursorIsHidden_4f1890(void);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsTwoPlayerCursorFadeOut_4f1930(void)
{
    if (insmenu_InsectVsTwoPlayerCursorIsHidden_4f1890() == 0) {
        func_290690(D_004FA180, 0x14, 0.0f, D_0047D3E0, -1.0f);
    }
}
