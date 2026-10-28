/* rgp:protos */
#define RGP_SELF_normal_LeaderHudBannerRefresh_507a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00507A30 -- the gp pointer D_0048456C is RE-READ at all four sites
 * (a call boundary forces it), so it is written as the global each time rather
 * than hoisted into a local, which would take a callee-saved register. */
extern void *D_0048456C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_LeaderHudBannerRefresh_507a30(void)
{
    s32 h;
    h = normal_LeaderHudBannerLayout_506370(D_0048456C, 7, 0, UiPageGetField38Related_289ac0(D_0048456C));
    UiPageGetField38Related_289ac0(D_0048456C);
    normal_LeaderHudSetBannerWidth_506ad0(D_0048456C, h);
    normal_LeaderHudBannerGaugeRefresh_507bb0();
    return h;
}
