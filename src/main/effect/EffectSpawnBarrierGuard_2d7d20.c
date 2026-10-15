#include "types.h"

/* lane N4 family: EffectSpawnBarrierGuard_2d7d20 / EffectSpawnBarrierGuard_2d7d20 (188 B each).
   Substitution: D_00461690 -> D_00461690. */

typedef struct { u8 d[0x20]; } Ctx;

extern u8 D_00461690[];
extern u8 D_00461688[];

extern void *GetEffectMgr_2d9040(void);
extern void EffectReleaseByNameKey_2e0e50(void *, void *, void *);
extern void EffectCreateByName_2e1020(Ctx *, void *, void *, s32);
extern void EffectSetId_2e0100(void *, Ctx *, void *);
extern void EffectSetPos_2e0bb0(void *, Ctx *, void *);
extern void EffectSetParamInt_2e0530(void *, Ctx *, s32, s32);
extern void EffectSetName_2e01c0(void *, Ctx *, void *);
extern void EffectStep_2e0e00(void *, Ctx *);

void EffectSpawnBarrierGuard_2d7d20(void *a0, void *a1)
{
    Ctx c;
    void *h;

    h = GetEffectMgr_2d9040();
    EffectReleaseByNameKey_2e0e50(h, D_00461690, a0);
    EffectCreateByName_2e1020(&c, h, D_00461690, -1);
    EffectSetId_2e0100(h, &c, a0);
    EffectSetPos_2e0bb0(h, &c, a1);
    EffectSetParamInt_2e0530(h, &c, 0, 0);
    EffectSetName_2e01c0(h, &c, D_00461688);
    EffectStep_2e0e00(h, &c);
}
