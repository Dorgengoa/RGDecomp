/* rgp:protos */
#define RGP_SELF_ObjRecSetFlags_1c3e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void * ObjRecLookup_1c3ef0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

struct Obj0 *ObjRecSetFlags_1c3e00(s32 p0, s32 p1, s32 p2, s32 p3)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = ObjRecLookup_1c3ef0(p0, p1, p2);
    if (r0 != 0) {
        t0 = r0->m00;
        r0->m00 = (t0 | p3);
    }
    return r0;
}
