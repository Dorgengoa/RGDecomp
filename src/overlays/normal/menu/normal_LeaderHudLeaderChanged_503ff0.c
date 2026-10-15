#include "types.h"
/* normal 0x00503FF0 -- three calls on the gp object at 0x0048456C.  The float
 * argument of the first is a plain 0.0f (`mtc1 $0, $f12`). */
extern void *D_0048456C;

extern void normal_LeaderHudSetWeaponGaugeShown_5069c0(void *p, f32 t);
extern void normal_LeaderHudBannerReshow_503720(void);
extern void normal_LeaderHudSetPanelMode_506b10(void *p, s32 k);

void normal_LeaderHudLeaderChanged_503ff0(void)
{
    normal_LeaderHudSetWeaponGaugeShown_5069c0(D_0048456C, 0.0f);
    normal_LeaderHudBannerReshow_503720();
    normal_LeaderHudSetPanelMode_506b10(D_0048456C, 1);
}
