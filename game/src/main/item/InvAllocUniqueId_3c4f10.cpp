#include "types.h"
#pragma opt_common_subs off
extern "C" u8 *PoolGetUsedElem_36acb0(s32, s32);
extern "C" u8 D_00465B50[0x400];

extern "C" s32 InvAllocUniqueId_3c4f10(u8 *arg0) {
    s32 result;
    s32 n;
    s32 i;
    bool found;
    s32 t;
    s32 j;
    u8 *p;

    if (*(s32 *)(arg0 + 0x168) == 0) {
        return -1;
    }
    result = -1;
    n = *(s32 *)D_00465B50;
    for (i = 0; i < n; i++) {
        found = false;
        for (j = 0; j < n; j++) {
            p = PoolGetUsedElem_36acb0(*(s32 *)(arg0 + 0x168), j);
            if (p != 0 && *(s32 *)(arg0 + 0x16C) == *(s16 *)(p + 6) && ((u64)((s64)*(u8 *)(p + 0xA) << 0x3E) >> 0x3F) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            result = *(s32 *)(arg0 + 0x16C);
        }
        t = *(s32 *)(arg0 + 0x16C) + 1;
        *(s32 *)(arg0 + 0x16C) = t;
        *(s32 *)(arg0 + 0x16C) = t & 0x7FFF;
        if (!found) {
            break;
        }
    }
    return result;
}
