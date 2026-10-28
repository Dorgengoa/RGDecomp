/* rgp:protos */
#define RGP_SELF_PtrArrayAlloc_30d490 1
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
    s32 m04;
    s32 m08;
    s32 m0C;
};

u8 PtrArrayAlloc_30d490(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    u16 ok;

    p0->m04 = 0;
    p0->m0C = 0;
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    if (p2 == 0) {
        return 0;
    }
    r0 = ((s32)BumpArenaAlloc_42e300((p1 << 2), p2, p3));
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    if (p1 == 0) {
        goto zero;
    }
    if (r0 != 0) {
        goto okl;
    }
zero:
    ok = 0;
    goto done;
okl:
    p0->m00 = r0;
    ok = 1;
    p0->m08 = p1;
done:
    return ok;
}
