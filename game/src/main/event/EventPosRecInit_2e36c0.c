/* rgp:protos */
#define RGP_SELF_EventPosRecInit_2e36c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
};

void EventPosRecInit_2e36c0(struct Obj0 *p0, s32 p1, s32 p2, f32 fa0, f32 fa1, f32 fa2)
{
    EventPosRecReset_2e3740(p0);
    EventRecInitWithKey_2e5800(p0, p1);
    p0->m10 = p2;
    p0->m14 = fa0;
    p0->m18 = fa1;
    p0->m1C = fa2;
}
