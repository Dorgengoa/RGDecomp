/* rgp:protos */
#define RGP_SELF_SoundSlotPlaySe_1d1a50 1
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

void SoundSlotPlaySe_1d1a50(s32 p0, s32 p1)
{
    s32 r0;
    f32 r1;

    r0 = SoundSlotGetHandle_1d2150(p0);
    r1 = SoundSlotGetVolume_1d2120(p0);
    SoundPlayScaledVolume_1b9520(r0, p1, 0, r1);
}
