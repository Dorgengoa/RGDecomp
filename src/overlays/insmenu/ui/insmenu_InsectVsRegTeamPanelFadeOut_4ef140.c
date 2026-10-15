#include "types.h"
/* insmenu 0x004EF140 -- the 004EE770 shape with a 0.0f first float, so that
 * literal is `mtc1 $0, $f12` and its lui disappears: 17 words. */
extern s32 insmenu_InsectVsRegTeamPanelIsHidden_4ef050(void);
extern const u8 D_004FA180[];
extern f32 D_0047D3D8;
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsRegTeamPanelFadeOut_4ef140(void)
{
    if (insmenu_InsectVsRegTeamPanelIsHidden_4ef050() == 0) {
        func_290690(D_004FA180, 0x53, 0.0f, D_0047D3D8, -1.0f);
    }
}
