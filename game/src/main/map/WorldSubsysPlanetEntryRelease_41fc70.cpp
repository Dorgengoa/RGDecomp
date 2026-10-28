/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    s32 v6(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x20, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
};

struct Obj1 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
};

extern "C" s32 WorldSubsysPlanetEntryRelease_41fc70(struct Obj1 *p0, struct Obj0 *p1, int rgp_a2, int rgp_a3)
{
    s16 n;
    s32 t;

    if (p1 == 0) {
        return 0;
    }
    n = p1->m08;
    if (n >= 0) {
        if (n < 2) {
            goto ok;
        }
    }
    return 0;
ok:
    t = p0->m08;
    if (t != 0) {
        ((struct C0 *)(t + ((n * 3) << 6)))->v6((int)(long)(p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    t = p0->m0C;
    if (t != 0) {
        ((struct C0 *)(t + ((n * 19) << 3)))->v6();
    }
    return 1;
}
