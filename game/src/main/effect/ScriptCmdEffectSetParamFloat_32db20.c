/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetParamFloat_32db20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void *D_004826E0;

s32 ScriptCmdEffectSetParamFloat_32db20(E8 *p0, s32 p1)
{
    u8 loc[32] __attribute__((aligned(16)));
    void *o;
    f32 t;
    s32 r;
    s32 m;

    if (p1 != 2 && p1 != 3) {
        return 0;
    }
    o = 0;
    switch (p1) {
    case 2:
        o = D_004826E0;
        break;
    case 3:
        o = D_004826E0;
        break;
    }
    if (o == 0) {
        return 0;
    }
    t = ScriptSlotGetFloat_334890(p0++);
    r = ScriptSlotGetInt_3348b0(p0);
    if (D_004826E0 == 0) {
        return 0;
    }
    m = ((s32)GetEffectMgr_2d9040());
    if (m == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(loc, D_004826E0);
    EffectSetParamFloat_2e0600(m, loc, r, t);
    return 1;
}
