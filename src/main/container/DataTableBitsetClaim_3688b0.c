#include "types.h"
#pragma opt_loop_invariants off

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x84 - 0x7E];
    u8 *unk84;
} Obj3688;

s32 DataTableBitsetClaim_3688b0(Obj3688 *arg0, s32 arg1) {
    u8 *p;
    u8 mask;
    s32 i;
    s32 n;

    p = arg0->unk84;
    if (p == NULL) {
        return 0;
    }
    n = arg0->unk7C;
    p += (u16)arg1 / 8;
    mask = 1 << ((u16)arg1 % 8);
    for (i = arg1 & 0xFFFF; i < n; ) {
        if (!(*p & mask)) {
            *p |= mask;
            break;
        }
        i++;
        if (i % 8 == 0) {
            p++;
            mask = 1;
        } else {
            mask <<= 1;
        }
    }
    return 1;
}
