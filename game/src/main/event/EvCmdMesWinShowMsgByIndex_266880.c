/* rgp:protos */
#define RGP_SELF_EvCmdMesWinShowMsgByIndex_266880 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_266880;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinShowMsgByIndex_266880(E8_266880 *p0)
{
    E8_266880 v[2] __attribute__((aligned(16)));
    s32 a;
    s32 b;
    s32 c;

    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetInt_26a2a0(p0);
    c = MsgGetTextByIndex_279040(b);
    ScriptArgInitInt_26a1b0(&v[0], a);
    ScriptArgInitCodeAddr_26a1a0(&v[1], c);
    return EvCmdMesWinShowMsg_2668f0(v, 2) != 0;
}
