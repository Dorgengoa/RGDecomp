/* rgp:protos */
#define RGP_SELF_SoundSlotPlaySeVol_1d1ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SoundSlotPlaySeVol_1d1ab0(s32 p0, s32 p1, f32 fa0)
{
    SoundSlotSetVolumeNow_1d2020(p0, fa0);
    SoundSlotPlaySe_1d1a50(p0, p1);
}
