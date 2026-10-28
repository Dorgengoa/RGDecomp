/* rgp:protos */
#define RGP_SELF_EventScriptRunTwoPass_2fd9d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj { s32 data[0x20A]; u8 flag; } Obj;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00451FF0[0x40];
extern u8 D_004520D0[0x40];
extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EventScriptRunTwoPass_2fd9d0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Obj a __attribute__((aligned(16)));
    Obj b __attribute__((aligned(16)));
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
    t = ((s32)GetEventObjMgr_2d1960());
    EventObjApplySaveStateMaybe_2e7a40(t);
    EventObjMgrResolveAllTargets_2e8840(t);
    return 1;
}
