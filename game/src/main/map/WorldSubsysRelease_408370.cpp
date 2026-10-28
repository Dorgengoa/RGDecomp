/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    s32 v6(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x20, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



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

extern "C" void WorldSubsysRelease_408370(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 t2;

    t0 = p0->m0C;
    if (t0 != 0) {
        ((struct C0 *)t0)->v6((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        t1 = p0->m10;
        rv1 = t1;
    } else {
        t2 = p0->m10;
        rv1 = t2;
    }
    if (rv1 != 0) {
        ((struct C0 *)rv1)->v6();
        return;
    }
}
