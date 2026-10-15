#include "types.h"

extern void * ObjRecTableGet_1c3fa0(s32, s32);
extern void MemStackRefCountInc_14d7e0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x14];
    s16 m18;
    s16 m1A;
    s32 m1C;
};

struct Obj0 *ObjRecSetRes_1c52a0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = ObjRecTableGet_1c3fa0(p0, p1);
    if (r0 != 0) {
        r0->m1C = p2;
        MemStackRefCountInc_14d7e0(p2);
        r0->m18 = p4;
        r0->m1A = p5;
        r0->m1C = p2;
        t0 = r0->m00;
        r0->m00 = (t0 | 1);
    }
}
