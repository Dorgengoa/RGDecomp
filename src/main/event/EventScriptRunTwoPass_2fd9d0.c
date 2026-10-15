#include "types.h"

typedef struct Obj { s32 data[0x20A]; u8 flag; } Obj;
s32 GetEventObjMgr_2d1960();
s32 EventObjApplySaveStateMaybe_2e7a40(s32);
s32 EventObjMgrResolveAllTargets_2e8840(s32);
s32 EvScriptTemplatesReset_301c20();
s32 EventScratchFree_301d30();
s32 EventScratchInit_301d70();
s32 CfgVmRun_42fa20(Obj *);
s32 CfgVmLoad_42fac0(Obj *, s32, s32);
s32 CfgVmRegisterCmds_42fb00(Obj *, u8 *);
s32 CfgVmReset_42fc10(Obj *);
extern u8 D_00451FF0[0x40];
extern u8 D_004520D0[0x40];
extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EventScriptRunTwoPass_2fd9d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Obj a;
    Obj b;
    s32 t;

    if (arg0 == 0) {
        return 0;
    }
    D_0047F0C0 = arg2;
    D_0047F0C4 = arg3;
    EventScratchInit_301d70();
    EvScriptTemplatesReset_301c20();
    CfgVmReset_42fc10(&a);
    a.flag = 1;
    CfgVmRegisterCmds_42fb00(&a, D_00451FF0);
    CfgVmLoad_42fac0(&a, arg0, arg1);
    CfgVmRun_42fa20(&a);
    CfgVmReset_42fc10(&b);
    b.flag = 1;
    CfgVmRegisterCmds_42fb00(&b, D_004520D0);
    CfgVmLoad_42fac0(&b, arg0, arg1);
    CfgVmRun_42fa20(&b);
    EventScratchFree_301d30();
    EvScriptTemplatesReset_301c20();
    t = GetEventObjMgr_2d1960();
    EventObjApplySaveStateMaybe_2e7a40(t);
    EventObjMgrResolveAllTargets_2e8840(t);
    return 1;
}
