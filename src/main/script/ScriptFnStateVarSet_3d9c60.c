#include "types.h"

extern s64 VariantGetS16_36fcc0(void);
extern void StateVarSet_3cc9c0(s32, s32, s64, s32);
extern void *D_00483960;
extern s32 D_00483964;
extern void *D_00483968;

void ScriptFnStateVarSet_3d9c60(s32 arg0, s32 *arg1) {
    s32 var_17;

    if (arg0 == 0 || arg1 == NULL) {
        return;
    }
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    var_17 = 0;
    if (D_00483968 != NULL) {
        var_17 = *(u8 *)((u8 *)D_00483968 + 0xE0C) & 1;
    }
    StateVarSet_3cc9c0(*(s32 *)((u8 *)D_00483960 + 0x10), *arg1,
                 (s64)(s16)VariantGetS16_36fcc0(), var_17);
}
