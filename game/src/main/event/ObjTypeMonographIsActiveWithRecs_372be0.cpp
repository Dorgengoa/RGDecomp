/* rgp:protos */
#line 1
#include "types.h"

struct C220 {
    u8 pad000[0xDC];
    VC_VPTR_MEMBER;
    
    
    s32 v3(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x14, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE0];
    s32 mE0;
    s32 mE4;
};

extern "C" s32 ObjTypeMonographIsActiveWithRecs_372be0(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    s32 t0;
    s32 rv1;
    s32 t1;

    r0 = ((struct C220 *)p0)->v3((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r0 == 0) {
        return 0;
    }
    t0 = p0->mE0;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        t1 = p0->mE4;
        rv1 = (t1 != 0);
    }
    return rv1;
}
