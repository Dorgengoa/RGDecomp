#include "types.h"

s32 ActCfgTableFindCmndByName_222db0(s32, s32);                         /* extern */
s32 ActDataSetCnctCount_225ca0(s32, s32);                           /* extern */
s32 ActDataGetCnctCount_225cd0(s32);                              /* extern */
s32 ActDataGetCnctList_225d00(s32);                              /* extern */
s32 ActDataCnctInit_227550(s32 *, s32, f32);                    /* extern */
s32 ScriptArgGetStr_23fba0();                              /* extern */
f32 ScriptArgGetFloat_23fbc0();                              /* extern */
s32 ActCfgGetCurTable_23ff20();                                 /* extern */
extern s32 D_00481EEC;

s32 ActDataCnct_23b440(s32 arg0, s32 arg1)
{
    s32 h;
    s32 *e;
    f32 f;

    if (arg1 != 1 && arg1 != 2) {
        return 0;
    }
    h = ActCfgGetCurTable_23ff20();
    if (h == 0) {
        return 1;
    }
    if (ActDataGetCnctList_225d00(h) == 0 || ActDataGetCnctCount_225cd0(h) >= 0x20) {
        return 1;
    }
    e = (s32 *)(ActDataGetCnctList_225d00(h) + ActDataGetCnctCount_225cd0(h) * 8);
    if (arg1 == 2) {
        f = ScriptArgGetFloat_23fbc0(arg0 + 8);
    } else {
        f = 1.0f;
    }
    ActDataCnctInit_227550(e, ActCfgTableFindCmndByName_222db0(D_00481EEC, ScriptArgGetStr_23fba0(arg0)), f);
    if (*e == 0) {
        return 1;
    }
    ActDataSetCnctCount_225ca0(h, ActDataGetCnctCount_225cd0(h) + 1);
    return 1;
}
