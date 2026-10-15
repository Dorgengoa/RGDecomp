#include "types.h"

s32 TargetRefGetId_2e7120(s32);
s32 EvObjGetTargetRef_2f9ca0(void *, s32);
s32 ScriptArgGetStr_301a00(s32);
s32 EventStrDup_301aa0(s32);
void EvTargetSetupMaybe_352ae0(s32, s32, s32, s32, s32, s32);
extern s32 D_00482890;
extern s32 D_00482894;
extern u8 D_004E7110[0x400];

s32 EvScriptCmdEvTargetAddNamed_2fdbe0(s32 arg0, s32 arg1)
{
    s32 b;
    s32 p;
    s32 a;

    if (arg1 != 2) {
        return 0;
    }
    if (D_00482890 == 0 || D_00482894 >= 0x20) {
        return 1;
    }
    p = D_00482890 + D_00482894 * 0x140;
    a = TargetRefGetId_2e7120(EvObjGetTargetRef_2f9ca0(D_004E7110, D_00482890));
    b = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0));
    EvTargetSetupMaybe_352ae0(p, a, b, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 8)), 0, 0);
    D_00482894 += 1;
    return 1;
}
