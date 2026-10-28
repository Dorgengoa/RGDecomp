/* rgp:protos */
#define RGP_SELF_NavXformPointToWorld_310d10 1
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
    u8 pad000[0x113];
    s8 m113;
};

void NavXformPointToWorld_310d10(struct Obj0 *p0, s32 p1, s32 p2)
{
    s8 t0;

    t0 = p0->m113;
    if (t0 != 0) {
        MatMulPoint_1cb8e0(p1, p0, (void *)p2);
    } else {
        VecCopy_1cbe30(p1, p2);
    }
}
