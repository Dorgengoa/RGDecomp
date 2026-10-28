/* rgp:protos */
#define RGP_SELF_BattleCmdResPendingReset_204e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481C20;
extern u8 D_00481C24;

s32 BattleCmdResPendingReset_204e60(void)
{
    u8 t0;
    s32 t1;

    t0 = D_00481C24;
    if (t0 != 0) {
        t1 = D_00481C20;
        if (t1 != -1) {
            D_00481C20 = -1;
            D_00481C24 = 0;
        }
    }
    return 1;
}
