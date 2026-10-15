#include "types.h"

#pragma divbyzerocheck on

typedef struct {
    u8 pad0[0x14];
    s16 unk14;
    u8 pad16[0xa];
    s16 unk20;
    s16 unk22;
} T323290_arg0;

void MinimapTileIndexToXY_323290(T323290_arg0 *arg0, s32 arg1, s32 *arg2, s32 *arg3)
{
    s32 a;
    s32 c;
    s32 q;
    s32 bb;

    *arg3 = 0;
    *arg2 = 0;
    a = arg0->unk20;
    bb = arg0->unk22;
    if (a == 0 || bb == 0 || (c = arg0->unk14) == 0) {
        return;
    }
    q = (s16)((s16)a / (s16)c);
    if (q != 0) {
        *arg2 = arg1 % (s16)q;
        *arg3 = arg1 / (s16)q;
        *arg2 *= arg0->unk14;
        *arg3 *= arg0->unk14;
    }
}
