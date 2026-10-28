/* rgp:protos */
#define RGP_SELF_EvScriptCmdFollowObjInit_300010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004E6880[0x400];

s32 EvScriptCmdFollowObjInit_300010(s32 arg0, s32 arg1)
{
    s32 a;

    EvScriptTemplatesReset_301c20();
    if (arg1 != 3 && arg1 != 4) {
        return 0;
    }
    if (arg1 > 3) {
        a = EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x18));
    } else {
        a = 0;
    }
    EvFollowObjInitByName_2f80e0(D_004E6880, EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0)), 0, a, ScriptArgGetAreaId_3019b0(arg0 + 8), EventStrDup_301aa0(ScriptArgGetStr_301a00(arg0 + 0x10)));
    return 1;
}
