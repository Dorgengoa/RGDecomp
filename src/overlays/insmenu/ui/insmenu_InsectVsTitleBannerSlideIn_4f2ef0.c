#include "types.h"
/* insmenu 0x004F2EF0 -- insmenu_InsectVsTitleBannerSlideOut_4f2ed0 with a leading call and -1 for
 * the fourth argument, so it needs a frame and the call is not a tail call. */
extern const u8 D_004FA180[];
extern f32 D_0047D1E8;
extern void insmenu_InsectVsTitleBannerLayout_4ea600(void);
extern void func_290F50(const void *a, s32 id, s32 c, s32 d, s32 e, f32 x);

void insmenu_InsectVsTitleBannerSlideIn_4f2ef0(void)
{
    insmenu_InsectVsTitleBannerLayout_4ea600();
    func_290F50(D_004FA180, 0x39, 0, -1, 0, D_0047D1E8);
}
