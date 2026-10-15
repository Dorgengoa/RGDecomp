#include "types.h"

extern s32 MinimapSlotIsActive_322510(u8 *e);
extern void MinimapSetWinSize_324c50(u8 *e, s32 b, s32 c);

void MinimapMgrSetWinSize_321a20(u8 *base, s32 b, s32 c)
{
    s32 i;
    u8 *e;

    for (i = 0; i < 3; i++) {
        e = base + i * 0x1B0;
        if (MinimapSlotIsActive_322510(e) == 0) continue;
        MinimapSetWinSize_324c50(e, b, c);
    }
}
