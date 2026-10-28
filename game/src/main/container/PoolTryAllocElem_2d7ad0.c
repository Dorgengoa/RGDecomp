/* rgp:protos */
#define RGP_SELF_PoolTryAllocElem_2d7ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 PoolTryAllocElem_2d7ad0(s32 p0, s32 p1)
{
    if (p1 != 0) {
        return (s32)PoolAllocElem_36ab00(p1, p0, 0);
        
    }
    return 0;
}
