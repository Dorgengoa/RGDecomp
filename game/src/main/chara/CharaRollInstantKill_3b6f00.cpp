/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v98(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x190, a0, a1); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v171(s32 a0) { return VCM(s32, (void *, s32), 0x2B4, a0); }
};

extern "C" s32 StatusRollChance_3b7050(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 CharaRollInstantKill_3b6f00(s32 p0, s32 p1, s32 p2, int rgp_a3)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv4;
    s32 r3;

    r0 = ((struct C0 *)p0)->v46((int)(long)(p1), (int)(long)(p2), (int)(long)(rgp_a3));
    if (r0 != 0) {
        return 0;
    }
    r1 = ((struct C0 *)p0)->v98(3, 1);
    r2 = StatusRollChance_3b7050(p0, p1, (r1 + p2));
    if ((r2 & 0xFF) == 0) {
        rv4 = 0;
    } else {
        r3 = ((struct C0 *)p0)->v171(1);
        rv4 = (r3 & 0xFF);
    }
    return rv4;
}
