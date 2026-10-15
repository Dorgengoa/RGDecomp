#include "types.h"

/* Named local for the accumulate keeps the add.s operand order
   (f20 + result). */

extern f32  MesWinGetOpenSpeed_277560(void *o);
extern void MesWinSetOpenRate_277550(void *o, f32 v);
extern f32  MesWinGetOpenRate_277540(void *o);
extern void MesWinAdvanceTypeout_275f00(void *o);
extern s32  MesWinGetScrollY_271700(void *o);
extern s32  MesWinGetScrollTarget_2716d0(void *o);
extern void MesWinSetScrollY_271710(void *o, s32 v);
extern void MesWinTickPageFrames_271e90(void *o);

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
