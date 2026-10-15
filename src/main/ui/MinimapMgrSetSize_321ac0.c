#include "types.h"

extern s32 MinimapSlotIsActive_322510(u8 *e);
extern void MinimapSetSizeClamped_324960(u8 *e, s32 b, s32 c);

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
