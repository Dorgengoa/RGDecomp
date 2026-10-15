#include "types.h"

extern void VariantSetS32_36f040(s32, s32, s32);
extern s32 VariantGetS8_36fe50(s32);
extern void GameDataBattleEnd_3e67c0(s32, s32, s32, s32, s32);

extern s32 D_00483960;
extern s32 D_00483964;

void ScriptFnBattleEnd_3d9150(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_16;
    s32 var_19;
    s32 var_18;

    var_16 = arg3;
    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    var_19 = 0;
    var_18 = 0;
    if (arg2 > 0) {
        var_19 = VariantGetS8_36fe50(var_16) != 0;
        var_16 += 0x38;
    }
    if (arg2 >= 2) {
        var_18 = VariantGetS8_36fe50(var_16) != 0;
    }
    GameDataBattleEnd_3e67c0(D_00483960, 1, var_19, var_18, 1);
}
