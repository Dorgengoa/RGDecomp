/* rgp:protos */
#line 1
#include "types.h"

struct C432 {
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v18(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x50, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x790];
    s32 m790;
    s32 m794;
    s32 m798;
    s32 m79C;
};

extern "C" s32 MapEntryReset_1e1350(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{ s32 rgp_v0;
    p0->m790 = 0;
    rgp_v0 = ((struct C432 *)p0)->v18((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    p0->m794 = 0;
    p0->m798 = 0x3F800000;
    p0->m79C = -1;
return rgp_v0; }
