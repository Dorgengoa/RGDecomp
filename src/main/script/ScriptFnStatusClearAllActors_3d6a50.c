#include "types.h"

extern void VariantSetS32_36f040(s32, s32, s32);
extern void CharaSysStatusClearAllActors_3a1de0(s32, s32, s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnStatusClearAllActors_3d6a50(s32 arg0) {
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    CharaSysStatusClearAllActors_3a1de0(*(s32 *)((u8 *)D_00483960 + 0x20), 0, 0, 0);
    VariantSetS32_36f040(arg0, 1, 1);
}
