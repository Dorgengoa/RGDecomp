#include "types.h"

extern void VariantSetS32_36f040(s32, s32, s32);
extern void StateVarSet_3cc9c0(s32, s32, s32, s32);
extern s16 StateVarGet_3ccac0(s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnStateVarIncrementMaybe_3d6f00(s32 arg0) {
    s32 var_6;

    if ((arg0 == 0) || (VariantSetS32_36f040(arg0, 0, 1), (D_00483960 == NULL)) || (D_00483964 == 0) || !(D_00483968 != 0)) {
        return;
    }
    {
        var_6 = (s16)(StateVarGet_3ccac0(*(s32 *)((u8 *)D_00483960 + 0x10), 0xE) + 1);
        if (var_6 <= 0) {
            var_6 = 0x7FFF;
        }
        StateVarSet_3cc9c0(*(s32 *)((u8 *)D_00483960 + 0x10), 0xE, var_6, 1);
        StateVarSet_3cc9c0(*(s32 *)((u8 *)D_00483960 + 0x10), 0x79, 2, 1);
        VariantSetS32_36f040(arg0, 1, 1);
    }
}
