/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlotStartFromData_1d0bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 GameSceneSoundSlotStartFromData_1d0bc0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)GameSceneSoundSlotGet_1d0de0(p0, p1));
    if (r0 != 0) {
        r1 = SoundSlotStartFromData_1d1e80(r0, p2);
        return r1;
    }
    return -1;
}
