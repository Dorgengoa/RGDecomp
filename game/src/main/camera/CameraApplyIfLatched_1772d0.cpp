/* rgp:protos */
#line 1
#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v14(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x40, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x108];
    s32 m108;
};

extern "C" void CameraApplyIfLatched_1772d0(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 t0;

    t0 = p0->m108;
    if (t0 != 0) {
        ((struct C192 *)p0)->v14((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    p0->m108 = 0;
}
