#include "types.h"
#pragma optimization_level 3
typedef struct {
    u8 pad0[0x40];
    s16 a40[0x20];
    u8 b80[0x20];
    s16 aA0[0x20];
    s16 aE0[0x20];
} S31c120;

void ScreenMarkerSlotFadeOutTick_31c120(S31c120 *arg0, s32 arg1)
{
    s32 idx;
    s16 *field;
    s16 val;

    idx = arg1;
    if (idx >= 0x20) {
        idx = 0x1F;
    }
    field = (s16 *)((u8 *)arg0->aA0 + idx * 2);
    val = *field;
    if (val >= 0) {
        *field = (s16)(val - 1);
    }
    if (*field <= 0) {
        arg0->a40[idx] = -1;
        arg0->b80[idx] = 2;
        *field = -1;
        arg0->aE0[idx] = -1;
    }
}
