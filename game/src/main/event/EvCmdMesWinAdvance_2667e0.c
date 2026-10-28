/* rgp:protos */
#define RGP_SELF_EvCmdMesWinAdvance_2667e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinAdvance_2667e0(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    r1 = MesMgrGetSlotWin_266af0(r0);
    if (r1 == 0) {
        return 0;
    }
    r2 = ((signed char)MesWinIsPageWait_2721f0(r1));
    if (r2 != 0) goto ok;
    return 1;
ok:
    MesWinAdvance_2768f0(r1);
    return 1;
}
