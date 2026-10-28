/* rgp:protos */
#define RGP_SELF_SkillLockClearResetSpot_3eb6c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004839A4;

void SkillLockClearResetSpot_3eb6c0(s32 p0, s32 p1)
{
    if (p1 != 0) {
        GameDataResetSpotState_3eb690(p0);
    }
    D_004839A4 = 0;
}
