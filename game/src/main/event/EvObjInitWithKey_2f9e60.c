/* rgp:protos */
#define RGP_SELF_EvObjInitWithKey_2f9e60 1
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
    u8 pad000[0xD0];
    s32 mD0;
};

void EvObjInitWithKey_2f9e60(struct Obj0 *p0, s32 p1, s32 p2)
{
    EvObjReset_2f9eb0(p0);
    EventRecInitWithKey_2e5800(p0, p1);
    p0->mD0 = p2;
}
