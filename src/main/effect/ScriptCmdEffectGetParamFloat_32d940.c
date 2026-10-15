#include "types.h"
#pragma opt_repositioncode on

s32 GetEffectMgr_2d9040();                                 /* extern */
s32 EffectCopyHandle_2dd3b0(u8 *, s32);                           /* extern */
s32 EffectGetParamFloat_2e0460(s32, u8 *, s32, f32 *);               /* extern */
s32 ScriptSlotStoreFloatRef_3347d0(s64 *, f32);                           /* extern */
s32 ScriptSlotGetInt_3348b0(s64 *);                              /* extern */
extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamFloat_32d940(s64 *arg0, s32 arg1) {
    f32 sp5C;
    s32 sp40[4];
    s32 temp_18;
    s32 temp_2;
    s32 var_3;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    var_3 = 0;
    switch (arg1) {
    case 2:
        var_3 = D_004826E0;
        break;
    case 3:
        var_3 = D_004826E0;
        break;
    }
    if (var_3 == 0) {
        return 0;
    }
    sp5C = 0;
    temp_18 = ScriptSlotGetInt_3348b0(arg0++);
    if (D_004826E0 == 0) {
        return 0;
    }
    temp_2 = GetEffectMgr_2d9040();
    if (temp_2 == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0((u8 *)sp40, D_004826E0);
    EffectGetParamFloat_2e0460(temp_2, (u8 *)sp40, temp_18, &sp5C);
    ScriptSlotStoreFloatRef_3347d0(arg0, sp5C);
    return 1;
}
