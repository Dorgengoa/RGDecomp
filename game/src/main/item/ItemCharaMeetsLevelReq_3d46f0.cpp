/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x70, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v56() { return VCM0(s32, 0xE8); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u8 ItemCharaMeetsLevelReq_3d46f0(s32 p0, s32 p1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    s32 r1;

    if (p1 == 0) {
        return (u8)0;
    }
    r0 = ((struct C0 *)p0)->v26((int)(long)(p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    r1 = ((struct C0 *)p1)->v56();
    return (r1 >= r0);
}
