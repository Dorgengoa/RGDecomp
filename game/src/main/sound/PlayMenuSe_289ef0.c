/* rgp:protos */
#define RGP_SELF_PlayMenuSe_289ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void PlayMenuSe_289ef0(s32 p0)
{
    s32 r0;

    r0 = SceneSoundGetSlot0HandleCur_207df0();
    SoundPlayScaledVolume_1b9520(r0, p0, 0, 1.0f);
}
