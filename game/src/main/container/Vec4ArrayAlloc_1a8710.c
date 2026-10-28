/* rgp:protos */
#define RGP_SELF_Vec4ArrayAlloc_1a8710 1
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
};

s32 Vec4ArrayAlloc_1a8710(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = ((s32)MemStackNew_14e1b0((p1 << 4), p2));
    p0->m04 = r0;
    if (r0 != 0) {
        p0->m00 = p1;
    }
    return r0;
}
