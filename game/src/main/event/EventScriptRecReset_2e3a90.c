/* rgp:protos */
#define RGP_SELF_EventScriptRecReset_2e3a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
};

void EventScriptRecReset_2e3a90(struct Obj0 *p0)
{
    EventRecReset_2e5840(p0);
    p0->m10 = 0;
    p0->m14 = 0;
}
