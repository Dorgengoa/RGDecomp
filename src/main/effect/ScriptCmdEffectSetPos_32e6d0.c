#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectCopyHandle_2dd3b0(void *, s32);
extern void EffectSetPos_2e0bb0(s32, void *, f32 *);
extern void ScriptSlotsToVec4_334810(f32 *, s32);
extern void ScriptSlotGetInt_3348b0(s32);
extern f32 D_0047F540;
extern f32 D_0047F544;
extern f32 D_0047F548;
extern f32 D_0047F54C;
extern s32 D_004826E0;


s32 ScriptCmdEffectSetPos_32e6d0(s64 *arg0, s32 arg1) {
    f32 v[4];
    u8 sp20[0x20];
    s32 t;

    if (arg1 != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)arg0++);
    v[0] = D_0047F540;
    v[1] = D_0047F544;
    v[2] = D_0047F548;
    v[3] = D_0047F54C;
    ScriptSlotsToVec4_334810(v, (s32)arg0);
    if (D_004826E0 == 0) {
        return 0;
    }
    t = GetEffectMgr_2d9040();
    if (t == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(sp20, D_004826E0);
    EffectSetPos_2e0bb0(t, sp20, v);
    return 1;
}
