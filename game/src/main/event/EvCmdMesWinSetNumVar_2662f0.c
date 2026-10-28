/* rgp:protos */
#define RGP_SELF_EvCmdMesWinSetNumVar_2662f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S8_002662f0 {
    s32 a;
    s32 b;
} S8_002662f0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinSetNumVar_2662f0(S8_002662f0 *a0)
{
    S8_002662f0 *p;
    void *h;
    s32 v1;
    s32 v2;

    p = a0;
    h = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(p++));
    if (h == 0) {
        return 0;
    }
    v1 = ScriptGetInt_26a2a0(p++);
    v2 = ScriptGetInt_26a2a0(p);
    if (v1 == 0) {
        MesWinSetNumVar0_2769c0(h, v2);
    } else {
        MesWinSetNumVar_2769a0(h, v1 - 1, v2, 0);
    }
    return 1;
}
