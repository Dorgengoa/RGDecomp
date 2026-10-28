/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineResultModelMotionIsFinished_2a8650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004824B8;

s32 MenuWeaponCombineResultModelMotionIsFinished_2a8650(void)
{
    s32 t0;
    s32 rv1;
    s32 r0;

    t0 = D_004824B8;
    rv1 = (r0 != 0);
    if (t0 == 0) {
        rv1 = 0;
    } else {
        r0 = MotionListIsFinished_171d90((t0 + 0x1F0), -1);
        rv1 = (r0 != 0);
    }
    return rv1;
}
