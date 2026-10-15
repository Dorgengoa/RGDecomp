#include "types.h"


extern void EffectInstanceGetParamFloat_2dd680(s32, s32, f32 *);
extern void ScriptSlotStoreFloatRef_3347d0(s64 *, f32);
extern s32 ScriptSlotGetInt_3348b0(s64 *);
extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamFloat_332d90(s64 *arg0, s32 arg1) {
    f32 sp3C;
    s32 var_17;
    s32 t;
    s32 sub;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    var_17 = 0;
    switch (arg1) {
    case 2:
        var_17 = D_004826E0;
        break;
    case 3:
        var_17 = D_004826E0;
        break;
    }
    if (var_17 == 0) {
        return 0;
    }
    sp3C = 0;
    EffectInstanceGetParamFloat_2dd680(var_17, ScriptSlotGetInt_3348b0(arg0++), &sp3C);
    ScriptSlotStoreFloatRef_3347d0(arg0, sp3C);
    return 1;
}
