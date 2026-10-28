/* rgp:protos */
#define RGP_SELF_NavEdgeGetOtherNode_3116b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
    s16 m02;
};

s32 NavEdgeGetOtherNode_3116b0(struct Obj0 *p0, s32 p1)
{
    s16 t0;
    s16 t1;
    s16 t2;

    t0 = p0->m00;
    if (p1 == t0) {
        t1 = p0->m02;
        return (s32)t1;
    }
    t2 = p0->m02;
    if (p1 == t2) {
        return (s32)t0;
    }
    return -1;
}
