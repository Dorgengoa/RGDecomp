/* rgp:protos */
#line 1
#include "types.h"

struct C32 {
    u8 pad000[0x20];
    VC_VPTR_MEMBER; s32 v0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    u8 m08;
    u8 pad009[0x1B];
    s32 m24;
};

extern "C" s32 ObjRecBind_1c4ef0(struct Obj0 *p0, s32 p1, s32 p2, int rgp_a3)
{
    s32 t0;

    if (p1 == 0) {
        return 0;
    }
    ((struct C32 *)p0)->v0((int)(long)(p1), (int)(long)(p2), (int)(long)(rgp_a3));
    p0->m00 = 0;
    p0->m24 = p1;
    if (p2 == 0) {
        p0->m08 = 0;
    } else {
        strcpy((struct Obj0 *)((u8 *)p0 + 8), p2);
    }
    t0 = p0->m00;
    p0->m00 = (t0 | 4);
    return 1;
}
