/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectCreateAt_32c920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdEffectCreateAt_32c920(E8 *p0, s32 p1)
{
    u8 loc[32] __attribute__((aligned(16)));
    s32 m;
    s32 k;
    s32 j;
    f32 a;
    f32 b;
    f32 c;
    f32 d;

    if (p1 < 5) {
        return 1;
    }
    m = ((s32)GetEffectMgr_2d9040());
    k = ScriptSlotGetCodeAddr_334870(p0);
    EffectCreateByName_2e1020(loc, m, k, -1);
    EffectSetAutoRelease_2e1170(m, loc, 1);
    j = ScriptSlotGetInt_3348b0(p0 + 1);
    EffectSetId_2e0100(m, loc, j);
    a = ScriptSlotGetFloat_334890(p0 + 2);
    b = ScriptSlotGetFloat_334890(p0 + 3);
    c = ScriptSlotGetFloat_334890(p0 + 4);
    EffectSetPosXyz_2e0ad0(m, loc, a, b, c);
    d = 0.0f;
    if (p1 > 5) {
        d = ScriptSlotGetFloat_334890(p0 + 5);
    }
    EffectSetRotXyz_2e0910(m, loc, 0.0f, d, 0.0f);
    return 1;
}
