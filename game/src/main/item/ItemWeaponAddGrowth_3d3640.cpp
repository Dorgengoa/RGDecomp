/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v24(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x68, a0, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x16];
    s8 m16;
};

extern "C" s32 ItemWeaponAddGrowth_3d3640(struct Obj0 *p0, s32 p1, int rgp_a2, int rgp_a3)
{
    s8 t0;
    s32 r0;
    s8 t1;

    t0 = p0->m16;
    r0 = ((struct C0 *)p0)->v24((t0 + p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    t1 = p0->m16;
    return (s8)(t1);
}
