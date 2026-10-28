/* rgp:protos */
#define RGP_SELF_MinimapMgrSetSize_321ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void MinimapMgrSetSize_321ac0(u8 *base, s32 b, s32 c)
{
    s32 i;
    u8 *e;

    for (i = 0; i < 3; i++) {
        e = base + i * 0x1B0;
        if (MinimapSlotIsActive_322510(e) == 0) continue;
        MinimapSetSizeClamped_324960(e, b, c);
    }
}
