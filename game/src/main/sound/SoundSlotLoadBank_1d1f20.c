/* rgp:protos */
#define RGP_SELF_SoundSlotLoadBank_1d1f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int SoundSlotLoadBank_1d1f20(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = SoundSlotGetBankId_1d2130(p0);
    r1 = ((s32)SoundSlotGetMemStack_1d2110(p0));
    return SoundBankLoad_1b9f00(r0, p1, r1);
}
