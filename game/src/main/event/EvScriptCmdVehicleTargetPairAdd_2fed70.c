/* rgp:protos */
#define RGP_SELF_EvScriptCmdVehicleTargetPairAdd_2fed70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/                              /* extern */
/*rgp*/            /* extern */
extern s32 D_00482878;
extern s32 D_0048287C;

s32 EvScriptCmdVehicleTargetPairAdd_2fed70(s32 arg0, s32 arg1) {
    s32 temp_19;
    s32 temp_18;
    s32 temp_17;
    s32 temp_16;

    if (arg1 != 4) {
        return 0;
    }
    if ((D_00482878 == 0) || (D_0048287C >= 0x20)) return 1;
    temp_19 = D_00482878 + (D_0048287C * 0x64);
    temp_18 = ScriptArgGetAreaId_3019b0(arg0);
    temp_17 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 8));
    temp_16 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10));
    ObjTypeVehicleTargetPairInit_3386b0(temp_19, temp_18, temp_17, temp_16, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x18)));
    D_0048287C += 1;
    return 1;
    return 1;
}
