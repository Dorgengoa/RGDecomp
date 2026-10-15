#include "types.h"

extern void VariantSetS32_36f040(s32, s32, s32);
extern void InvSpecialItemRestoreMaybe_3e4250(s32);
extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnInvSpecialItemRestoreMaybe_3d6fd0(s32 arg0) {
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    InvSpecialItemRestoreMaybe_3e4250(D_00483960);
    VariantSetS32_36f040(arg0, 1, 1);
}
