#include "types.h"

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCreateByName_2e1020(void *, s32, void *, s32);
extern void EffectSetAutoRelease_2e1170(s32, void *, s32);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void CharaRequestTint_213fd0(s32, s32, s32, f32, f32, f32, f32, f32);
typedef unsigned __int128 u128;

extern u8 D_004616D0[];

void EffectPlayHeal_2d80e0(s32 p0)
{
    u128 v40[2];
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetActionMgr_1fdb50();
    r1 = ActionMgrFindById_233b50(r0, p0);
    if (r1 != 0) {
        r2 = GetEffectMgr_2d9040();
        EffectCreateByName_2e1020(v40, r2, D_004616D0, -1);
        EffectSetAutoRelease_2e1170(r2, v40, 1);
        EffectSetId_2e0100(r2, v40, p0);
        CharaRequestTint_213fd0(r1, 4, 1, 72.0f, 160.0f, 224.0f, 15.0f, 1.0f);
    }
}
