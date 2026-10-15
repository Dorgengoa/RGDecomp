#include "types.h"

s32 MemStackAlign64_14d8e0(s32);
s32 MemStackAllocQw_14d950(s32, s32);
s32 MemStackPeekQw_14d9d0(s32, s32);
s32 MemStackReturnToOwnerMaybe_14dad0(s32);
s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
s32 MemStackHeapFree_14dcb0(s32, s32);
s32 ResidentFileReadLocalizedMaybe_1c2860(void *, s32, s32 *);
s32 GetGameData_1fede0();
s32 GetReadBuffHeap_2025e0();
s32 GetEffectMgr_2d9040();
s32 GetEffectFixHeap_2d9050();
s32 EffectArchiveLoadByName_2e28a0(void *, s32, s32, s32, s32, s32);
extern s32 D_0044B650[];
extern s32 D_0045C0B0[];

void StaticEffectLoad_2014a0(void) {
    s32 t19;
    s32 t2;
    s32 t17;
    s32 t16;
    s32 t21;
    s32 *p;
    s32 t5;

    s32 sp70[4];
    s32 sp8C;

    t19 = GetEffectMgr_2d9040();
    GetGameData_1fede0();
    t2 = GetReadBuffHeap_2025e0();
    t17 = MemStackHeapAlloc_14db10(t2, 2, 0, 0x40);
    MemStackAlign64_14d8e0(t2);
    t5 = MemStackPeekQw_14d9d0(t2, 1);
    t16 = t5;
    sp8C = 0;
    if ((ResidentFileReadLocalizedMaybe_1c2860(D_0045C0B0, t5, &sp8C) & 0xFF) && (sp8C > 0)) {
        MemStackAllocQw_14d950(t2, sp8C / 16 + 1);
        MemStackReturnToOwnerMaybe_14dad0(t2);
        t21 = GetEffectFixHeap_2d9050();
        for (p = D_0044B650; p[0] != 0; p += 2) {
            EffectArchiveLoadByName_2e28a0(sp70, t19, t21, p[0], t16, p[1]);
        }
    } else {
        MemStackReturnToOwnerMaybe_14dad0(t2);
    }
    MemStackHeapFree_14dcb0(t2, t17);
}
