/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlotRequestLoad_1d0b20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 GameSceneSoundSlotRequestLoad_1d0b20(s32 p0, s32 p1, s32 p2, s32 p3)
{
    u128 v60[8];
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 r2;

    r0 = ((s32)GameSceneSoundSlotGet_1d0de0(p0, p1));
    if (r0 == 0) {
        return 0;
    }
    r1 = GameSceneSoundMakeBankPath_1d0c40(p0, v60, p1, p2, p3);
    if (r1 < 0) {
        rv3 = 1;
    } else {
        r2 = SoundSlotRequestLoad_1d1d90(r0, r1, v60);
        rv3 = r2;
    }
    return rv3;
}
