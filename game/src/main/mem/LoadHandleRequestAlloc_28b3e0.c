/* rgp:protos */
#define RGP_SELF_LoadHandleRequestAlloc_28b3e0 1
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
struct Obj1;

struct Obj0 {
    s32 m00;
};

struct Obj1 {
    s32 m00;
};

s32 LoadHandleRequestAlloc_28b3e0(struct Obj1 *p0, struct Obj0 *p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r0;
    s32 t0;

    if (p4 == 0) {
        return -1;
    }
    r0 = MemStackAllocAligned64_14da10(p4, 0xF081);
    p1->m00 = r0;
    LoadHandleRequest_28b470(p0, p2, p3, r0, 0xF080, p5);
    t0 = p0->m00;
    return t0;
}
