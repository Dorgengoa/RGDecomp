/* rgp:protos */
#define RGP_SELF_IdBitmapClearBit_1f50f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

void IdBitmapClearBit_1f50f0(void *self, s32 idx)
{
    s32 base;
    s32 diff;
    s32 r;
    u8 *p;

    if (*(void **)((u8 *)self + 4) == 0 || idx < (base = *(s16 *)((u8 *)self + 0)) || *(s16 *)((u8 *)self + 2) <= idx) {
        return;
    }
    diff = idx - base;
    p = (u8 *)(*(void **)((u8 *)self + 4)) + diff / 8;
    r = diff % 8;
    *p = ((1 << r) ^ 0xFFFF) & 0xFF & *p;
}
