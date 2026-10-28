/* rgp:protos */
#define RGP_SELF_EvSwitchRecMulMatrix_2f8700 1
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

void EvSwitchRecMulMatrix_2f8700(s32 p0, s32 p1, s32 p2)
{
    u128 v30[4];

    EvSwitchRecBuildMatrix_2f8750(p0, v30);
    MatMul_1cb700(p1, p2, v30);
}
