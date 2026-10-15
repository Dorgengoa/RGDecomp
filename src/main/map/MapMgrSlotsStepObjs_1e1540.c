#include "types.h"

extern void MapAreaActiveBlocksStepObjs_1d9040(u8 *q, f32 x);

void MapMgrSlotsStepObjs_1e1540(u8 *p, f32 x)
{
    u8 *q;
    s32 i;

    q = p + 0x1928;
    for (i = 0; i < 4; i++) {
        MapAreaActiveBlocksStepObjs_1d9040(q, x);
        q += 0x1CC;
    }
}
