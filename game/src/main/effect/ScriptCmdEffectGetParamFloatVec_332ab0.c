/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectGetParamFloatVec_332ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamFloatVec_332ab0(s64 *arg0, s32 arg1) {
    f32 f[4] __attribute__((aligned(16)));
    s32 v;

    if (arg1 < 4) {
        goto fail;
    }
    if (arg1 > 6) {
    fail:
        return 0;
    }
    v = 0;
    switch (arg1) {
    case 4:
    case 5:
        v = D_004826E0;
        break;
    case 6:
        v = D_004826E0;
        break;
    }
    EffectInstanceGetParamFloatVec_2dd5f0(v, ScriptSlotGetInt_3348b0((s32)arg0++), f);
    ScriptSlotStoreFloatRef_3347d0((s32)arg0++, f[0]);
    ScriptSlotStoreFloatRef_3347d0((s32)arg0++, f[1]);
    ScriptSlotStoreFloatRef_3347d0((s32)arg0++, f[2]);
    if (arg1 > 4) {
        ScriptSlotStoreFloatRef_3347d0((s32)arg0, f[3]);
    }
    return 1;
}
