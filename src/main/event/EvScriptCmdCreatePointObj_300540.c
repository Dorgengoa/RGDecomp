#include "types.h"

extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjMgrCreatePointObj_2ea0b0(s32, s32, s32, void *);
extern void EvPointObjCtorWithPoint_2f97f0(void *, s32, s32, f32, f32, f32, f32);
extern s32 ScriptArgGetStr_301a00(s32);
extern f32 ScriptArgGetFloat_301a20(s32);
extern void EvScriptTemplatesReset_301c20(void);
extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EvScriptCmdCreatePointObj_300540(s32 arg0, s32 arg1) {
    u8 sp40[0xE0];
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    s32 temp_16;

    EvScriptTemplatesReset_301c20();
    if (arg1 != 5) {
        return 0;
    }
    temp_16 = ScriptArgGetStr_301a00(arg0);
    temp_f22 = ScriptArgGetFloat_301a20(arg0 + 8);
    temp_f21 = ScriptArgGetFloat_301a20(arg0 + 0x10);
    temp_f20 = ScriptArgGetFloat_301a20(arg0 + 0x18);
    EvPointObjCtorWithPoint_2f97f0(sp40, temp_16, 0, temp_f22, temp_f21, temp_f20, ScriptArgGetFloat_301a20(arg0 + 0x20));
    EventObjMgrCreatePointObj_2ea0b0(GetEventObjMgr_2d1960(), D_0047F0C0, D_0047F0C4, sp40);
    return 1;
}
