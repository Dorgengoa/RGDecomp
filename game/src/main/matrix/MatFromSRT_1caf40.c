/* rgp:protos */
#define RGP_SELF_MatFromSRT_1caf40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MatFromSRT_1caf40(s32 p0, s32 p1, s32 p2, s32 p3)
{
    u128 v30[4];

    MatFromRotPos_1caf90(v30, p2, p3);
    MatScaleRows_1cbc20(p0, v30, p1);
}
