#include "types.h"

/* insmenu 0x004F4EA0 (96 bytes, 24 instructions, 5 calls) -- enter the page:
 * set the mode, run the page builder, cue the two widget animations.
 * 0x9CAA and 0x88B9 do not fit a signed 16-bit immediate, which is why they
 * are `ori` and not `addiu`.
 */

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern f32 D_0047D3BC;

extern void func_376B20(s32 a);
extern void insmenu_InsectVsLoadWidgetsFade_4f6ac0(s32 a);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void insmenu_InsectVsLoadPanelLayout_4f7dd0(void);
extern void func_28EA90(const void *a, s32 b, s32 c);

s32 insmenu_InsectVsTeamListCancel_4f4ea0(void)
{
    func_376B20(6);
    insmenu_InsectVsLoadWidgetsFade_4f6ac0(2);
    func_290690(D_004FA180, 0x9CAA, 0.0f, D_0047D3BC, 0.0f);
    insmenu_InsectVsLoadPanelLayout_4f7dd0();
    func_28EA90(D_004FA1A0, 0x88B9, 0);
    return 1;
}
