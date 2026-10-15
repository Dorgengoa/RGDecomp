#include "types.h"

extern s32 D_00483960;
extern s32 D_00483964;
extern void VariantSetS32_36f040(s32, s32, s32);
extern void GameDataBattleEnd_3e67c0(s32, s32, s32, s32, s32);

void ScriptFnBattleEndCode2_3d90f0(s32 arg0)
{
    if (arg0 != 0) {
        VariantSetS32_36f040(arg0, 0, 1);
        if (D_00483960 == 0 || D_00483964 == 0) {
            return;
        }
        GameDataBattleEnd_3e67c0(D_00483960, 2, 0, 1, 0);
    }
}
