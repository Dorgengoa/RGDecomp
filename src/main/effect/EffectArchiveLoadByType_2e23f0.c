#include "types.h"

extern void EffectArchiveLoadImgChecked_2e1930(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void EffectArchiveLoadChrChecked_2e1ae0(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void EffectArchiveLoadEfp_2e1c90(void *, s32, s32, s32, s32, s32, s32, s32);

void EffectArchiveLoadByType_2e23f0(s16 *a0, s32 a1, s32 a2, s32 sel, s32 a4, s32 a5, s32 a6, s32 a7, s32 s0, s32 s8, s32 s10)
{
    switch (sel) {
    case 1:
        EffectArchiveLoadEfp_2e1c90(a0, a1, a2, a4, a5, a7, s0, s10);
        return;
    case 2:
        EffectArchiveLoadChrChecked_2e1ae0(a0, a1, a2, a4, a5, a6, a7, s0, s8, s10);
        return;
    case 3:
        EffectArchiveLoadImgChecked_2e1930(a0, a1, a2, a4, a5, a6, a7, s0, s8, s10);
        return;
    default:
        a0[0] = 0;
        *(s32 *)((u8 *)a0 + 0x4) = -1;
        *(s32 *)((u8 *)a0 + 0x8) = 0;
        *(s32 *)((u8 *)a0 + 0xC) = -1;
        return;
    }
}
