/* rgp:protos */
#define RGP_SELF_EffTableSetSubHeapMaybe_1a10a0 1
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

void EffTableSetSubHeapMaybe_1a10a0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;

    if (p1 != 0) {
        EffTableClearRefs_1a1040(p0);
        p0->m0C = p1;
        p0->m10 = p1;
        t0 = p0->m0C;
        MemStackRefCountInc_14d7e0(t0);
        t1 = p0->m10;
        MemStackRefCountInc_14d7e0(t1);
        return;
    }
}
