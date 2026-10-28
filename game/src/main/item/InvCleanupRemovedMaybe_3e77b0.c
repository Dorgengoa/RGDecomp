/* rgp:protos */
#define RGP_SELF_InvCleanupRemovedMaybe_3e77b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

s32 InvCleanupRemovedMaybe_3e77b0(struct Obj0 *p0)
{
    s32 t0;
    s32 rv3;
    s32 t1;
    s32 t2;
    s32 r2;

    t0 = p0->m18;
    rv3 = 1;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        PartyResetSpotTimeAndDistMaybe_3c96b0(t0);
        t1 = p0->m18;
        InvFreeCategory8Items_3c8d70(t1);
        t2 = p0->m18;
        r2 = InvPurgeRemoved_3c8cc0(t2);
        rv3 = 1;
    }
    return rv3;
}
