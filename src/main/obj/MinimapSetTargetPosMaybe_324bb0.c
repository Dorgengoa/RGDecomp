#include "types.h"
#pragma opt_common_subs off

extern void memcpy(void *dst, const void *src, s32 n);

void MinimapSetTargetPosMaybe_324bb0(void *arg0, void *arg1) {
    s32 flag;
    s32 hasFlag;

    memcpy((u8 *)arg0 + 0x10, arg1, 0x10);
    flag = *(s8 *)((u8 *)arg0 + 0x11A);
    hasFlag = 0;
    if (flag & 2) {
        hasFlag = 1;
        *(s8 *)((u8 *)arg0 + 0x11A) = flag & ~2;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x170) != 0 && *(s32 *)((u8 *)arg0 + 0x174) == 0) || hasFlag != 0) {
        memcpy(arg0, (u8 *)arg0 + 0x10, 0x10);
    }
}
