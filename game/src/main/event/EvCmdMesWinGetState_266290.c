/* rgp:protos */
#define RGP_SELF_EvCmdMesWinGetState_266290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinGetState_266290(E8 *p)
{
    void *r;
    void *q;

    r = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(p++));
    if (r == 0) {
        return 0;
    }
    q = MesWinGetState_276a80(r);
    ScriptSetRefInt_26a1e0(p, q);
    return 1;
}
