#include "types.h"

extern s32 GetTreasureBoxPool_3389b0(void);
extern s32 GameFlowGetTreasureBoxId_285ec0(void);
extern s32 TreasureBoxPoolFindById_339150(s32, s32);
extern s32 TreasureBoxTrapApply_33a400(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdTreasureBoxTrapApply_25e560(void)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv4;
    s32 r3;

    r0 = GetTreasureBoxPool_3389b0();
    r1 = GameFlowGetTreasureBoxId_285ec0();
    r2 = TreasureBoxPoolFindById_339150(r0, r1);
    rv4 = r2;
    if (r2 != 0) {
        r3 = TreasureBoxTrapApply_33a400(r2);
        rv4 = r3;
    }
    return 1;
}
