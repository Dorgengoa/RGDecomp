#include "types.h"
#pragma opt_loop_invariants off

extern void EffDefUnlinkByHandle_1a0040(s32 arg0, s32 arg1);
extern void EffectEntriesReleaseAllNodes_2de390(s32 arg0);

void EffectMgrUnlinkActive_2e1550(void *arg0)
{
    s32 i;
    u8 *cur;

    EffectEntriesReleaseAllNodes_2de390((s32)((u8 *)arg0 + 0x1674));
    i = 0;
    do {
        cur = (u8 *)arg0 + i * 0x70;
        if ((*(s32 *)(cur + 0x174) >= 0) && (*(u8*)(cur + 0x1E0) == 1)) {
            EffDefUnlinkByHandle_1a0040((s32)((u8 *)arg0 + 0x58), *(s32 *)(cur + 0x178));
        }
        i += 1;
    } while (i < 0x30);
}
