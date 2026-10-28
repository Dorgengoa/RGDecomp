/* rgp:protos */
#define RGP_SELF_ActDataCnctGetCmndMask_2274c0 1
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
    s32 m00;
};

long long ActDataCnctGetCmndMask_2274c0(struct Obj0 *p0)
{
    s32 t0;
    long long r0;

    t0 = p0->m00;
    if (t0 != 0) {
        r0 = ActInfoCmndGetMask_2311f0(t0);
        return r0;
    }
    return 0;
}
