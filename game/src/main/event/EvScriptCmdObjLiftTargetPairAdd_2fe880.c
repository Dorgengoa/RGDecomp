/* rgp:protos */
#define RGP_SELF_EvScriptCmdObjLiftTargetPairAdd_2fe880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00451F70[];
extern s32 D_00482880;
extern s32 D_00482884;
extern u8 D_004E7000[];

s32 EvScriptCmdObjLiftTargetPairAdd_2fe880(u8 * arg0, s32 arg1) {
    s32 var_18;
    s8 *temp_19;
    s32 temp_21;
    s8 *temp_2;
    s32 var_16;

    if ((arg1 != 3) && (arg1 != 4)) {
        return 0;
    }
    if (D_00482880 != 0 && D_00482884 < 0x20) {
        goto body;
    }
    return 1;
body:
    temp_21 = D_00482880 + (D_00482884 * 0x68);
    var_18 = ((short)TargetRefGetId_2e7120(((s32)EvObjGetTargetRef_2f9ca0(D_004E7000))));
    temp_2 = ((s8 *)EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0)));
    if ((temp_2 == NULL) || (*temp_2 == 0)) {
        var_18 = -1;
    }
    var_16 = 3;
    if (arg1 > 3) {
        var_16 = ParseFlagNames_1ca700(ScriptArgGetStr_301a00(arg0 + 0x18), D_00451F70, 0);
    }
    temp_19 = ((s8 *)EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 8)));
    EvObjLiftTargetPairInit_337000(temp_21, var_18, temp_2, temp_19, ((s8 *)EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10))), var_16);
    D_00482884 += 1;
    return 1;
}
