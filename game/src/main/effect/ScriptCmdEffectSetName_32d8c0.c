/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetName_32d8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of ScriptCmdEffectSetId_32e160 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

extern s32 D_004826E0;

s32 ScriptCmdEffectSetName_32d8c0(s32 p0)
{
    u128 v30[2];
    s32 r0;
    s32 t0;
    s32 r1;
    s32 rv4;
    s32 t1;
    s32 r3;

    r0 = ScriptSlotGetCodeAddr_334870(p0);
    t0 = D_004826E0;
    if (t0 == 0) {
        return 0;
    }
    r1 = ((s32)GetEffectMgr_2d9040());
    rv4 = 1;
    if (r1 == 0) {
        rv4 = 0;
    } else {
        t1 = D_004826E0;
        EffectCopyHandle_2dd3b0(v30, t1);
        r3 = (EffectSetName_2e01c0(r1, v30, r0), (s32)0);
        rv4 = 1;
    }
    return rv4;
}
