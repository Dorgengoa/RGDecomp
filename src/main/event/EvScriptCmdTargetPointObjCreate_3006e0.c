#include "types.h"

s32 LookupNameValueNoCase_1cab50(s32, void *, s32);
s32 GetEventObjMgr_2d1960();
void EventObjMgrCreateTargetPointObj_2ea110(s32, s32, s32, void *);
void EvTargetPointObjCtorWithKey_2f9580(void *, s32, s32, s32, s32, s32, f32, f32);
s32 ScriptArgGetAreaId_3019b0(s32);
s32 ScriptArgGetStr_301a00(s32);
f32 ScriptArgGetFloat_301a20(s32);
void EvScriptTemplatesReset_301c20();
extern u8 D_00451E10[0x400];
extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EvScriptCmdTargetPointObjCreate_3006e0(s32 arg0, s32 arg1) {
    u8 sp70[0xF0];
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    f32 f;

    EvScriptTemplatesReset_301c20();
    if (arg1 != 6) {
        return 0;
    }
    a = ScriptArgGetStr_301a00(arg0);
    b = LookupNameValueNoCase_1cab50(ScriptArgGetStr_301a00(arg0 + 8), D_00451E10, 0);
    c = ScriptArgGetAreaId_3019b0(arg0 + 0x10);
    d = ScriptArgGetStr_301a00(arg0 + 0x18);
    f = ScriptArgGetFloat_301a20(arg0 + 0x20);
    EvTargetPointObjCtorWithKey_2f9580(sp70, a, 0, b, c, d, f, ScriptArgGetFloat_301a20(arg0 + 0x28));
    EventObjMgrCreateTargetPointObj_2ea110(GetEventObjMgr_2d1960(), D_0047F0C0, D_0047F0C4, sp70);
    return 1;
}
