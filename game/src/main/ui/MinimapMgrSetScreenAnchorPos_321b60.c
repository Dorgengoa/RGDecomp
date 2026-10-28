/* rgp:protos */
#define RGP_SELF_MinimapMgrSetScreenAnchorPos_321b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void MinimapMgrSetScreenAnchorPos_321b60(u8 *base, s32 b, s32 c)
{
    s32 i;
    u8 *e;

    for (i = 0; i < 3; i++) {
        e = base + i * 0x1B0;
        if (MinimapSlotIsActive_322510(e) == 0) continue;
        MinimapSetScreenAnchorPos_324ca0(e, b, c);
    }
}
