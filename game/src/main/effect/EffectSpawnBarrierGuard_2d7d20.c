/* rgp:protos */
#define RGP_SELF_EffectSpawnBarrierGuard_2d7d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* lane N4 family: EffectSpawnBarrierGuard_2d7d20 / EffectSpawnBarrierGuard_2d7d20 (188 B each).
   Substitution: D_00461690 -> D_00461690. */

typedef struct { u8 d[0x20]; } Ctx;

extern u8 D_00461690[];
extern u8 D_00461688[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EffectSpawnBarrierGuard_2d7d20(void *a0, void *a1)
{
    Ctx c __attribute__((aligned(16)));
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
