/* rgp:protos */
#define RGP_SELF_SaveCalcSizeKBCurrent_37b920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004831D0;

s32 SaveCalcSizeKBCurrent_37b920(void)
{
    s32 t0;
    s32 r0;

    t0 = D_004831D0;
    if (t0 != 0) {
        r0 = SaveCalcSizeKB_3735e0(t0);
        return r0;
    }
    return 0;
}
