/* rgp:protos */
#define RGP_SELF_AiCmdStateFlagSet_2c78f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdStateFlagSet_2c78f0(s64 *arg0)
{
    s32 a;
    void *t;

    t = GetGameData_1fede0();
    switch (*(s32 *)arg0) {
    case 0:
    case 1:
        a = ScriptSlotGetInt_2cc9c0(arg0++);
        StateFlagSet_3ccb70(*(s32 *)((u8 *)t + 0x10), a, ScriptSlotGetInt_2cc9c0(arg0) != 0, 1);
        break;
    case 2:
        a = ScriptSlotGetCodeAddr_2cc980(arg0++);
        StateFlagSetByName_3ccaf0(*(s32 *)((u8 *)t + 0x10), a, ScriptSlotGetInt_2cc9c0(arg0) != 0, 1);
        break;

    }
    return 1;
}
