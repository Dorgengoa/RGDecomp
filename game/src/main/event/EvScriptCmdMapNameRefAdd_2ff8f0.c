/* rgp:protos */
#define RGP_SELF_EvScriptCmdMapNameRefAdd_2ff8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_dead_assignments off

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00482868;
extern s32 D_0048286C;

s32 EvScriptCmdMapNameRefAdd_2ff8f0(s32 pad0, s32 arg1) {
    s32 temp;

    if (arg1 != 1) {
        return 0;
    }
    if ((D_00482868 == 0) || (D_0048286C >= 0x20)) return 1;
    temp = D_00482868 + D_0048286C * 4;
    EvMapNameRefInit_3675b0(temp, EventStrDup_301aa0(ScriptArgGetStr_301a00(pad0)));
    D_0048286C += 1;
    return 1;
    return 1;
}
