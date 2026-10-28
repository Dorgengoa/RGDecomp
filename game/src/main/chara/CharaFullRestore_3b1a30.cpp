/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v46(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v59(s32 a0) { return VCM(s32, (void *, s32), 0xF4, a0); }
    
    
    
    
    
    
    s32 v66(s32 a0) { return VCM(s32, (void *, s32), 0x110, a0); }
    
    
    
    
    
    s32 v72(s32 a0) { return VCM(s32, (void *, s32), 0x128, a0); }
    
    s32 v74(s32 a0) { return VCM(s32, (void *, s32), 0x130, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v103(s32 a0) { return VCM(s32, (void *, s32), 0x1A4, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v200(s32 a0) { return VCM(s32, (void *, s32), 0x328, a0); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

extern "C" s32 CharaFullRestore_3b1a30(struct Obj0 *p0, s32 p1, s32 p2, int rgp_a3)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 rv3;
    s32 r2;
    s32 t1;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;

    r0 = ((struct C0 *)p0)->v46((int)(long)(p1), (int)(long)(p2), (int)(long)(rgp_a3));
    if (r0 != 0) {
        if (p1 == 0) {
            return 0;
        }
    } else {
        t0 = p0->m00;
    }
    r1 = ((struct C0 *)p0)->v46();
    rv3 = r1;
    if ((r1 & 0xFF) != 0) {
        r2 = ((struct C0 *)p0)->v103(1);
        rv3 = r2;
    } else {
        t1 = p0->m00;
        rv3 = r1;
    }
    r4 = ((struct C0 *)p0)->v72(1);
    r5 = ((struct C0 *)p0)->v59(r4);
    r6 = ((struct C0 *)p0)->v74(1);
    r7 = ((struct C0 *)p0)->v66(r6);
    if ((r1 & 0xFF) != 0) {
        r8 = ((struct C0 *)p0)->v200(p2);
        return 1;
    }
    return 1;
}
