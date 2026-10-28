/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetParamInt_32dc10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s8 *D_004826E0;

s32 ScriptCmdEffectSetParamInt_32dc10(s8 *arg0, s32 arg1) {
    s32 temp_18;
    s32 temp_17;
    s32 sp40[5] __attribute__((aligned(16)));
    s32 temp_2;
    s64 *var_16;
    s8 *var_3;

    var_16 = (s64 *)arg0;
    if (arg1 != 2 && arg1 != 3) {
        return 0;
    }
    var_3 = NULL;
    switch (arg1) {
    case 2:
        var_3 = D_004826E0;
        break;
    case 3:
        var_3 = D_004826E0;
        var_16++;
        break;
    }
    if (var_3 == NULL) {
        return 0;
    }
    temp_18 = ScriptSlotGetInt_3348b0((s8 *)var_16++);
    temp_17 = ScriptSlotGetInt_3348b0((s8 *)var_16);
    if (D_004826E0 == NULL) {
        return 0;
    }
    temp_2 = ((s32)GetEffectMgr_2d9040());
    if (temp_2 == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(sp40, D_004826E0);
    EffectSetParamInt_2e0530(temp_2, sp40, temp_18, temp_17);
    return 1;
}
