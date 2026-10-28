/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    s32 v6(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x20, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
};

struct Obj1 {
    u8 pad000[0xC];
    s32 m0C;
    u8 pad010[0x4];
    s32 m14;
};

extern "C" s32 WorldSubsysPlanetEntryRelease_40ec10(struct Obj1 *p0, struct Obj0 *p1, int rgp_a2, int rgp_a3)
{
    s16 t0;
    s32 t1;

    if (p1 == 0) {
        return 0;
    }
    t0 = p1->m08;
    if (t0 >= 0) {
        if (t0 < 2) goto ok;
    }
    return 0;
ok:
    t1 = p0->m0C;
    if (t1 != 0) {
        ((struct C0 *)(t1 + t0 * 992))->v6((int)(long)(p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    t1 = p0->m14;
    if (t1 != 0) {
        ((struct C0 *)(t1 + t0 * 152))->v6();
    }
    return 1;
}
