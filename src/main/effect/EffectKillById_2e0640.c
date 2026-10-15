#include "types.h"

extern void EffectFindHandleById_2dd6c0(void *, void *, s32);
extern void EffectKill_2e06c0(s32, s64 *);

s32 EffectKillById_2e0640(s32 arg0, s32 arg1) {
    u8 frame[0x34];

    *(s32 *)(frame + 0x2C) = 0;
    EffectFindHandleById_2dd6c0(frame, (u8 *)arg0 + 0x1674, arg1);
    *(s32 *)(frame + 0x2C) = *(s32 *)(frame + 0xC);
    *(s32 *)(frame + 0x28) = *(s32 *)(frame + 8);
    if (*(s32 *)(frame + 0x28) != -1) {
        *(s64 *)(frame + 0x2C) = *(s64 *)(frame + 0xC);
        *(s64 *)(frame + 0x20) = *(s64 *)(frame + 0);
        EffectKill_2e06c0(arg0, (s64 *)(frame + 0x20));
    }
    return 0;
}
