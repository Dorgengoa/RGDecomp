/* rgp:protos */
#define RGP_SELF_EvCmdMesWinIsPageWait_266540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct QFUN_00266540 { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinIsPageWait_266540(struct QFUN_00266540 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_26a2a0(q++);
    b = MesMgrGetSlotWin_266af0(a);
    if (b == 0) {
        return 0;
    }
    ScriptSetRefInt_26a1e0(q, MesWinGetState_276a80(b) == 5);
    return 1;
}
