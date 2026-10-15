#include "types.h"
/* normal 0x00503720 -- pure tail call (`j`, not `jal`): the whole body is the
 * forwarded call, so it must be spelled as a `return` of the callee. */

extern void *D_0048456C;          /* gp - 0xC04 */

extern s32 normal_LeaderHudSetBannerPhase_506b30(void *p, s32 a);

s32 normal_LeaderHudBannerReshow_503720(void)
{
    return normal_LeaderHudSetBannerPhase_506b30(D_0048456C, 1);
}
