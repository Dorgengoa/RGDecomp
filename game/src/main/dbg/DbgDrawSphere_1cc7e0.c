/* rgp:protos */
#define RGP_SELF_DbgDrawSphere_1cc7e0 1
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

void DbgDrawSphere_1cc7e0(s32 p0, s32 p1, s32 p2, f32 fa0)
{
    u128 v30[4];

    MatFromPosScale_1cb2b0(v30, p1, fa0);
    DrawWireSphere_1cc830(p0, v30, p2);
}
