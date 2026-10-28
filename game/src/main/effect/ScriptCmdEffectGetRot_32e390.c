/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectGetRot_32e390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047F570;
extern f32 D_0047F574;
extern f32 D_0047F578;
extern f32 D_0047F57C;
extern s32 D_004826E0;

s32 ScriptCmdEffectGetRot_32e390(s64 *arg0, s32 arg1)
{
    f32 v[4] __attribute__((aligned(16)));
    s32 buf[8] __attribute__((aligned(16)));
    s32 h;
    s32 p;

    if (arg1 != 2 && arg1 != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)arg0++);
    v[0] = D_0047F570;
    v[1] = D_0047F574;
    v[2] = D_0047F578;
    v[3] = D_0047F57C;
    if (D_004826E0 == 0) {
        return 0;
    }
    h = ((s32)GetEffectMgr_2d9040());
    if (h == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(buf, D_004826E0);
    EffectGetRot_2e0870(h, buf, v);
    if (arg1 == 2) {
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, v[1]);
    }
    if (arg1 == 4) {
        ScriptSlotStoreVec3_334790((s32)arg0, v);
    }
    return 1;
}
