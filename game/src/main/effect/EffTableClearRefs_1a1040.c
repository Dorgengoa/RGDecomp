/* rgp:protos */
#define RGP_SELF_EffTableClearRefs_1a1040 1
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
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
};

void EffTableClearRefs_1a1040(struct Obj0 *p0)
{
    s32 t0;
    s32 rv2;
    s32 t1;
    s32 t2;

    EffTableUnlinkAll_1a0120(p0);
    t0 = p0->m0C;
    if (t0 != 0) {
        MemStackRefCountDec_14d7c0(t0);
        t1 = p0->m10;
        rv2 = t1;
    } else {
        t2 = p0->m10;
        rv2 = t2;
    }
    if (rv2 != 0) {
        MemStackRefCountDec_14d7c0(rv2);
        p0->m0C = 0;
    } else {
        p0->m0C = 0;
    }
    p0->m10 = 0;
}
