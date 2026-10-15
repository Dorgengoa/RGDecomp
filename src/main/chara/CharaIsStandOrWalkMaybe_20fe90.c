#include "types.h"

typedef struct S0020fe90 {
    u8 pad0[0x860];
    u8 unk860;
    u8 pad861[0xA2E - 0x861];
    s16 unkA2E;
    u8 pad30[0xA32 - 0xA30];
    s16 unkA32;
    s16 unkA34;
} S0020fe90;

s32 CharaIsStandOrWalkMaybe_20fe90(S0020fe90 *arg0)
{
    s16 v;

    if (arg0->unkA2E != 0) {
        return 0;
    }
    if (arg0->unkA32 != 0) {
        return 0;
    }
    v = arg0->unkA34;
    if (v != 0x1F && v != 0x1E && v != 1 && v != 0) {
        return 0;
    }
    return !arg0->unk860;
}
