#include "types.h"

s32 ParseFlagNames_1ca700(s32, void *, s32);
s32 TargetRefGetId_2e7120(s32);
s32 EvObjGetTargetRef_2f9ca0(void *, s32);
s32 ScriptArgGetStr_301a00(u8 *);
s8 *EventStrDup_301aa0(s32);
void EvObjLiftTargetPairInit_337000(s32, s32, s8 *, s8 *, s8 *, s32);
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
    var_18 = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7000, D_00482880));
    temp_2 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0));
    if ((temp_2 == NULL) || (*temp_2 == 0)) {
        var_18 = -1;
    }
    var_16 = 3;
    if (arg1 > 3) {
        var_16 = ParseFlagNames_1ca700(ScriptArgGetStr_301a00(arg0 + 0x18), D_00451F70, 0);
    }
    temp_19 = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 8));
    EvObjLiftTargetPairInit_337000(temp_21, var_18, temp_2, temp_19, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10)), var_16);
    D_00482884 += 1;
    return 1;
}
