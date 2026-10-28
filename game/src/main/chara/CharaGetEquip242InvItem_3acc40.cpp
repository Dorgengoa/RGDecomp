/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v237(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x3BC, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 InvFindByUniqueId_3c85d0(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj0 * D_00483818;

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
};

extern "C" s32 CharaGetEquip242InvItem_3acc40(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct Obj0 * t0;
    s32 r0;
    s32 rv2;
    struct Obj0 * t1;
    s32 t2;
    s32 r1;

    t0 = D_00483818;
    if (t0 == 0) {
        return 0;
    }
    r0 = ((struct C0 *)p0)->v237((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r0 < 0) {
        rv2 = 0;
    } else {
        t1 = D_00483818;
        t2 = D_00483818->m18;
        r1 = InvFindByUniqueId_3c85d0(t2, r0, -1, 0);
        rv2 = r1;
    }
    return rv2;
}
