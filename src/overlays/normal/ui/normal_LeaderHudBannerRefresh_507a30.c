#include "types.h"
/* normal 0x00507A30 -- the gp pointer D_0048456C is RE-READ at all four sites
 * (a call boundary forces it), so it is written as the global each time rather
 * than hoisted into a local, which would take a callee-saved register. */
extern void *D_0048456C;
extern void *func_289AC0(void *a);
extern s32 normal_LeaderHudBannerLayout_506370(void *a, s32 b, s32 c, void *d);
extern void normal_LeaderHudSetBannerWidth_506ad0(void *a, s32 b);
extern void normal_LeaderHudBannerGaugeRefresh_507bb0(s32 a, s32 b);

s32 normal_LeaderHudBannerRefresh_507a30(void)
{
    s32 h;
    h = normal_LeaderHudBannerLayout_506370(D_0048456C, 7, 0, func_289AC0(D_0048456C));
    func_289AC0(D_0048456C);
    normal_LeaderHudSetBannerWidth_506ad0(D_0048456C, h);
    normal_LeaderHudBannerGaugeRefresh_507bb0(0, h != 0);
    return h;
}
