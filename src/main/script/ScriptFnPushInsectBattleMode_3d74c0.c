#include "types.h"

extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;
extern void VariantSetS32_36f040(void *p, s32 a, s32 b);
extern void GameReqQueuePushBack_1f5b50(s32 a, s32 b);

void ScriptFnPushInsectBattleMode_3d74c0(void *p0)
{
    if (p0 == 0) {
        return;
    }
    VariantSetS32_36f040(p0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    GameReqQueuePushBack_1f5b50(0xF, -1);
    VariantSetS32_36f040(p0, 1, 1);
}
