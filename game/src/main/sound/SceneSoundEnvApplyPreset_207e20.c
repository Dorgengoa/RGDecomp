/* rgp:protos */
#define RGP_SELF_SceneSoundEnvApplyPreset_207e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int SceneSoundEnvApplyPreset_207e20(s32 p0, s32 p1)
{
    s32 r0;

    r0 = GetCurrentScene_1f5be0();
    return GameSceneSoundEnvApplyPreset_1d0e30(r0, p0, 0, p1);
}
