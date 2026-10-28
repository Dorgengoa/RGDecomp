/* rgp:protos */
#define RGP_SELF_EvCmdMesWinGetFrameType_266230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinGetFrameType_266230(void *a0)
{
    void *q;
    void *x;
    void *y;

    q = a0;
    a0 = (u8 *)a0 + 8;
    x = ScriptGetInt_26a2a0(q);
    y = MesMgrGetSlotWin_266af0(x);
    if (y == 0) {
        return 0;
    }
    ScriptSetRefInt_26a1e0(a0, MesWinGetFrameTypeThunk_272b20(y));
    return 1;
}
