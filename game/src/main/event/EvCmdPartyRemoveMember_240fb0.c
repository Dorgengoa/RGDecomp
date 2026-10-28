/* rgp:protos */
#define RGP_SELF_EvCmdPartyRemoveMember_240fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdPartyRemoveMember_240fb0(s64 *arg0, s32 arg1)
{
    s32 temp_19;
    s32 var_2;
    u8 *temp_18;

    if ((arg1 != 1) || (arg1 != 2)) {
        return 0;
    }
    temp_18 = (u8 *)GetGameData_1fede0();
    temp_19 = ScriptGetInt_2490f0((s32)arg0++);
    var_2 = 0;
    if (arg1 == 2) {
        var_2 = ScriptGetInt_2490f0((s32)arg0);
    }
    if (!(PartyRemoveMember_3c0fa0(*(s32 *)(temp_18 + 0x18), temp_19, var_2 != 0, 0) != 0)) {
        return 0;
    }
    return 1;
    return 0;
}
