/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v168() { return VCM0(s32, 0x2A8); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_00483818;

extern "C" s32 UnitBaseOnDamagedByMaybe_3b1390(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 t0;
    s32 r0;
    s32 rv2;
    s32 r1;

    t0 = D_00483818;
    if (t0 == 0) {
        return 0;
    }
    r0 = ((struct C0 *)p0)->v46((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r0 != 0) {
        rv2 = 0;
    } else {
        r1 = ((struct C0 *)p0)->v168();
        rv2 = (r1 != 0) ^ 1;
    }
    return rv2;
}
