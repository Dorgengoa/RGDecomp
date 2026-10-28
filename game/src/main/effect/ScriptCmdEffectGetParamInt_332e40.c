/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectGetParamInt_332e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004826E0;

s32 ScriptCmdEffectGetParamInt_332e40(s64 *arg0, s32 arg1) {
    s32 sp3C;
    s32 var_17;
    s32 t;
    s32 sub;

    if ((arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    var_17 = 0;
    switch (arg1) {
    case 2:
        var_17 = D_004826E0;
        break;
    case 3:
        var_17 = D_004826E0;
        break;
    }
    if (var_17 == 0) {
        return 0;
    }
    sp3C = 0;
    EffectInstanceGetParamInt_2dd660(var_17, ScriptSlotGetInt_3348b0(arg0++), &sp3C);
    ScriptSlotStoreIntRef_3347f0(arg0, sp3C);
    return 1;
}
