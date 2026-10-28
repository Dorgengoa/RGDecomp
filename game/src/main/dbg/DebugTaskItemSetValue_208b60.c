/* rgp:protos */
#define RGP_SELF_DebugTaskItemSetValue_208b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 DebugTaskItemSetValue_208b60(s32 p0, s32 p1)
{
    s32 r0;

    r0 = TaskEntryOfDebugItem_208c00(p0);
    if (r0 != 0) {
        TaskSetFlag_1f5750(r0, p1, 0);
        TaskSetFlag_1f5750(r0, p1, 1);
    }
}
