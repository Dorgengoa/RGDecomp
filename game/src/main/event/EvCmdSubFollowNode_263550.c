/* rgp:protos */
#define RGP_SELF_EvCmdSubFollowNode_263550 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSubFollowNode_263550(s64 *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 d;
    s32 c;
    s32 r;
    u128 sp60;

    d = 0;
    sp60 = 0;
    switch (arg1) {
    case 3:
        a = ScriptGetInt_26a2a0(arg0++);
        b = ScriptGetInt_26a2a0(arg0++);
        c = ScriptGetCodeAddr_26a200(arg0);
        break;
    case 4:
        a = ScriptGetInt_26a2a0(arg0++);
        b = ScriptGetInt_26a2a0(arg0++);
        c = ScriptGetCodeAddr_26a200(arg0++);
        d = ScriptGetInt_26a2a0(arg0);
        break;
    case 6:
        a = ScriptGetInt_26a2a0(arg0++);
        b = ScriptGetInt_26a2a0(arg0++);
        c = ScriptGetCodeAddr_26a200(arg0++);
        ScriptArgsToVec4_26a220(&sp60, arg0);
        break;
    case 7:
        a = ScriptGetInt_26a2a0(arg0++);
        b = ScriptGetInt_26a2a0(arg0++);
        c = ScriptGetCodeAddr_26a200(arg0++);
        ScriptArgsToVec4_26a220(&sp60, arg0);
        d = ScriptGetInt_26a2a0(arg0 + 3);
        break;
    }
    r = ((s32)EvtGetSubMachine_26abb0(a));
    if (r == 0) {
        return 0;
    }
    EventSubNodeAddFollowNode_251620(r, b, c, d, &sp60);
    return 1;
}
