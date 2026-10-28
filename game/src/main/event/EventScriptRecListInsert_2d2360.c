/* rgp:protos */
#define RGP_SELF_EventScriptRecListInsert_2d2360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventScriptRecListInsert_2d2360(s32 p0, s32 p1)
{
    DListPushBack_42e5a0(p0, p1);
}
