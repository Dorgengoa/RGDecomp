/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v76() { return VCM0(s32, 0x138); }
    s32 v77() { return VCM0(s32, 0x13C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v102(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x1A0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void InsectItemSetAdult_3d11b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" void InsectItemCheckBecomeAdult_3cf880(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    s32 r1;
    s32 r2;

    if (p0 != 0) {
        r0 = ((struct C0 *)p0)->v102((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        if ((r0 & 0xFF) != 0) {
            return;
        }
        r1 = ((struct C0 *)p0)->v77();
        r2 = ((struct C0 *)p0)->v76();
        if (r1 <= (r2 + -0x14)) {
            InsectItemSetAdult_3d11b0(p0, 1);
        }
        return;
    }
}
