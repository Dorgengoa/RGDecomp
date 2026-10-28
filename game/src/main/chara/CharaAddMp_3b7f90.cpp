/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v66(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x110, a0, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    u16 m18;
};

extern "C" u32 CharaAddMp_3b7f90(struct Obj0 *p0, s32 p1, int rgp_a2, int rgp_a3)
{
    u16 t0;
    s32 r0;
    u16 t1;

    t0 = p0->m18;
    r0 = ((struct C0 *)p0)->v66((t0 + p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    t1 = p0->m18;
    return (u16)(t1);
}
