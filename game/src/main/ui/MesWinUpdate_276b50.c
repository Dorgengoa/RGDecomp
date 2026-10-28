/* rgp:protos */
#define RGP_SELF_MesWinUpdate_276b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Named local for the accumulate keeps the add.s operand order
   (f20 + result). */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinUpdate_276b50(void *o)
{
    f32 t;

    if (MesWinGetOpenSpeed_277560(o) == 0.0f) {
        MesWinSetOpenRate_277550(o, 1.0f);
    } else {
        if (MesWinGetOpenRate_277540(o) < 1.0f) {
            t = MesWinGetOpenRate_277540(o);
            MesWinSetOpenRate_277550(o, t + MesWinGetOpenSpeed_277560(o));
        }
        if (1.0f < MesWinGetOpenRate_277540(o)) {
            MesWinSetOpenRate_277550(o, 1.0f);
        }
    }
    MesWinAdvanceTypeout_275f00(o);
    if (MesWinGetScrollY_271700(o) <= MesWinGetScrollTarget_2716d0(o)) {
        MesWinSetScrollY_271710(o, MesWinGetScrollTarget_2716d0(o));
    }
    MesWinTickPageFrames_271e90(o);
}
