/* rgp:protos */
#define RGP_SELF_EvCmdMesWinIsTextDone_2665a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct QFUN_002665a0 { s32 a; s32 b; };

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinIsTextDone_2665a0(struct QFUN_002665a0 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_26a2a0(q++);
    b = MesMgrGetSlotWin_266af0(a);
    if (b == 0) {
        return 0;
    }
    ScriptSetRefInt_26a1e0(q, MesWinGetState_276a80(b) == 3);
    return 1;
}
