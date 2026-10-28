/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v45(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xBC, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v168() { return VCM0(s32, 0x2A8); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x198];
    s32 m198;
};

extern "C" s32 UnitBaseClearDeathTime_3b1530(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    s32 r1;
    s32 rv3;
    s32 t0;
    s32 rv2;

    r0 = ((struct C0 *)p0)->v45((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r0 == 0) {
        return 0;
    }
    r1 = ((struct C0 *)p0)->v168();
    if (r1 != 0) {
        rv3 = 0;
    } else {
        t0 = p0->m198;
        rv2 = 1;
        if (t0 <= 0) {
            rv2 = 0;
        } else {
            p0->m198 = -1;
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
