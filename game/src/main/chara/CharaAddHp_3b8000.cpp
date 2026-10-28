/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v59(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0xF4, a0, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
};

extern "C" s32 CharaAddHp_3b8000(struct Obj0 *p0, s32 p1, int rgp_a2, int rgp_a3)
{
    s32 t0;
    s32 r0;
    s32 t1;

    t0 = p0->m14;
    r0 = ((struct C0 *)p0)->v59((t0 + p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    t1 = p0->m14;
    return t1;
}
