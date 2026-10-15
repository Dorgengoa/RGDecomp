#include "types.h"
/* insmenu 0x004F2ED0 -- a single six-argument tail call.  D_0047D1E8 is
 * gp - 0x7F88, inside the gp window, so it is NOT const. */
extern const u8 D_004FA180[];
extern f32 D_0047D1E8;
extern void func_290F50(const void *a, s32 id, s32 c, s32 d, s32 e, f32 x);

void insmenu_InsectVsTitleBannerSlideOut_4f2ed0(void)
{
    func_290F50(D_004FA180, 0x39, 0, -0x3C, 0, D_0047D1E8);
}
