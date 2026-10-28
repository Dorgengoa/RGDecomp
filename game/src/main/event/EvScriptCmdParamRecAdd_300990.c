/* rgp:protos */
#define RGP_SELF_EvScriptCmdParamRecAdd_300990 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- early return rewrite + sp40 is a 0x20-byte buffer (frame 0x60). */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0047F0C0;
extern s32 D_0047F0C4;

s32 EvScriptCmdParamRecAdd_300990(s32 arg0, s32 arg1)
{
    u8 sp40[0x20] __attribute__((aligned(16)));
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_16;

    EvScriptTemplatesReset_301c20();
    if (arg1 != 4) {
        return 0;
    }
    temp_16 = ScriptArgGetStr_301a00(arg0);
    temp_f21 = ScriptArgGetFloat_301a20(arg0 + 8);
    temp_f20 = ScriptArgGetFloat_301a20(arg0 + 0x10);
    EventParamRecCtorInit_2e3c80(sp40, temp_16, temp_f21, temp_f20, ScriptArgGetFloat_301a20(arg0 + 0x18));
    EventObjMgrAddParamRec_2ea170(((s32)GetEventObjMgr_2d1960()), D_0047F0C0, D_0047F0C4, sp40);
    return 1;
    return 0;
}
