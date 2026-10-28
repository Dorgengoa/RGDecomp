/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetTargetParamsMaybe_32e1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
struct S8 { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004826E0;

s32 ScriptCmdEffectSetTargetParamsMaybe_32e1e0(struct S8 *p0)
{
    u128 v50[2];
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = ScriptSlotGetInt_3348b0(p0++);
    r1 = ScriptSlotGetInt_3348b0(p0++);
    r2 = ScriptSlotGetInt_3348b0(p0);
    if (D_004826E0 == 0) {
        return 0;
    }
    r3 = ((s32)GetEffectMgr_2d9040());
    if (r3 == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(v50, D_004826E0);
    EffectSetTargetRefParamsMaybe_2e0dc0(r3, v50, r0, r1, r2);
    return 1;
}
