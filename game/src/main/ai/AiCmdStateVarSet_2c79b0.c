/* rgp:protos */
#define RGP_SELF_AiCmdStateVarSet_2c79b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct G002c79b0 {
    u8 pad0[0x10];
    s32 unk10;
} G002c79b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCmdStateVarSet_2c79b0(s64 *arg0)
{
    G002c79b0 *g;
    s32 a;
    s64 b;

    g = ((G002c79b0 *)GetGameData_1fede0());
    switch (*(s32 *)arg0) {
    case 0:
    case 1:
        b = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        StateVarSet_3cc9c0(g->unk10, (int)(b), ScriptSlotGetInt_2cc9c0((s32)arg0), 1);
        break;
    case 2:
        a = ScriptSlotGetCodeAddr_2cc980((s32)arg0++);
        StateVarSetByName_3cc940(g->unk10, a, ScriptSlotGetInt_2cc9c0((s32)arg0), 1);
        break;
    }
    return 1;
}
