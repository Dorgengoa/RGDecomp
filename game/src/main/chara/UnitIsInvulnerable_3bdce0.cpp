/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x408];
    u8 m408;
};

extern "C" u64 UnitIsInvulnerable_3bdce0(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    u8 t0;

    r0 = ((struct C0 *)p0)->v46((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r0 != 0) {
        return (u64)0;
    }
    t0 = p0->m408;
    return (((u64)(((s64)t0) << 0x3C)) >> 0x3F);
}
