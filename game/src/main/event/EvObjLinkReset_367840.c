/* rgp:protos */
#define RGP_SELF_EvObjLinkReset_367840 1
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
    u8 pad000[0xE0];
    s32 mE0;
};

void EvObjLinkReset_367840(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    p0->mE0 = 0;
}
