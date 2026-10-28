/* rgp:protos */
#define RGP_SELF_VecAddThunk_13be20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void VecAddThunk_13be20(s32 p0, void *rgp_a1, void *rgp_a2)
{
    VecAdd_13be20(p0, (void *)rgp_a1, (void *)rgp_a2);
}
