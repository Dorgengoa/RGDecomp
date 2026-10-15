#include "types.h"

extern s32 GetEffectMgr_2d9040();
extern void EffectCopyHandle_2dd3b0(u8 *, s32);
extern void EffectGetParamIntVec_2e0200(s32, u8 *, s32, s32 *);
extern void ScriptSlotStoreIntRef_3347f0(s32, s32);
extern s32 ScriptSlotGetInt_3348b0(s32);
extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamIntVec_32df60(s64 *arg0, s32 arg1) {
    s32 sp70[4];
    u8 sp50[0x20];
    s32 n;
    s32 h;

    if (arg1 < 4 || arg1 > 6) {
        return 0;
    }

    n = ScriptSlotGetInt_3348b0((s32)arg0++);
    if (D_004826E0 == 0) {
        return 0;
    }
    h = GetEffectMgr_2d9040();
    if (h == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(sp50, D_004826E0);
    EffectGetParamIntVec_2e0200(h, sp50, n, sp70);
    ScriptSlotStoreIntRef_3347f0((s32)arg0++, sp70[0]);
    ScriptSlotStoreIntRef_3347f0((s32)arg0++, sp70[1]);
    ScriptSlotStoreIntRef_3347f0((s32)arg0++, sp70[2]);
    if (arg1 > 4) {
        ScriptSlotStoreIntRef_3347f0((s32)arg0, sp70[3]);
    }
    return 1;
}
