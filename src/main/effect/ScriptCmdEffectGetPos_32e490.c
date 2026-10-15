#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectCopyHandle_2dd3b0(void *arg0, s32 arg1);
extern void EffectGetPos_2e08c0(s32 arg0, void *arg1, f32 *arg2);
extern void ScriptSlotStoreVec3_334790(s32 arg0, f32 *arg1);
extern void ScriptSlotGetInt_3348b0(s32);
extern f32 D_0047F560;
extern f32 D_0047F564;
extern f32 D_0047F568;
extern f32 D_0047F56C;
extern s32 D_004826E0;

s32 ScriptCmdEffectGetPos_32e490(s64 *arg0, s32 arg1)
{
    f32 sp50[4];
    u8 sp30[0x20];
    s32 t;

    if (arg1 != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)arg0++);
    sp50[0] = D_0047F560;
    sp50[1] = D_0047F564;
    sp50[2] = D_0047F568;
    sp50[3] = D_0047F56C;
    if (D_004826E0 == 0) {
        return 0;
    }
    t = GetEffectMgr_2d9040();
    if (t == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(sp30, D_004826E0);
    EffectGetPos_2e08c0(t, sp30, sp50);
    ScriptSlotStoreVec3_334790((s32)arg0, sp50);
    return 1;
}
