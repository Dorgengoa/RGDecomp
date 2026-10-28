/* rgp:protos */
#define RGP_SELF_normal_LeaderHudLeaderChanged_503ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00503FF0 -- three calls on the gp object at 0x0048456C.  The float
 * argument of the first is a plain 0.0f (`mtc1 $0, $f12`). */
extern void *D_0048456C;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_LeaderHudLeaderChanged_503ff0(void)
{
    normal_LeaderHudSetWeaponGaugeShown_5069c0(D_0048456C, 0.0f);
    normal_LeaderHudBannerReshow_503720();
    normal_LeaderHudSetPanelMode_506b10(D_0048456C, 1);
}
