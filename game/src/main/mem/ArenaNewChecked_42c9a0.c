/* rgp:protos */
#define RGP_SELF_ArenaNewChecked_42c9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 ArenaNewChecked_42c9a0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    if (p1 != 0) {
        return (s32)ArenaAllocAligned_370330(p1, p0, p2, p3);
        
    }
    return 0;
}
