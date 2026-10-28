/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v101(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x19C, a0, rgp_fwd2, rgp_fwd3); }
    s32 v102(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x1A0, a0, a1, a2); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 CharaCureStatus9Maybe_3b1260(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = ((struct C0 *)p0)->v101(9, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    rv2 = r0;
    if (r0 != 0) {
        r1 = ((struct C0 *)p0)->v102(9, 0, 1);
        rv2 = r1;
    }
    return 1;
}
