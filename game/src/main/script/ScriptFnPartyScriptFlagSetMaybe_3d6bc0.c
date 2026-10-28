/* rgp:protos */
#define RGP_SELF_ScriptFnPartyScriptFlagSetMaybe_3d6bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnPartyScriptFlagSetMaybe_3d6bc0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 var_5;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    var_5 = 1;
    if (arg2 > 0) {
        var_5 = ((signed char)VariantGetS8_36fe50(arg3)) != 0;
    }
    PartyScriptFlagSetMaybe_3c9760(*(s32 *)((u8 *)D_00483960 + 0x18), var_5);
    VariantSetS32_36f040(arg0, 1, 1);
}

