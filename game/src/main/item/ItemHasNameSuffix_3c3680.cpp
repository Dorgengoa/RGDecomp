/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v41(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xAC, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u32 ItemHasNameSuffix_3c3680(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;

    r0 = ((struct C0 *)p0)->v41((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return (u8)((r0 >= 0));
}
