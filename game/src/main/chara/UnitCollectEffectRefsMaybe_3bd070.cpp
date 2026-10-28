/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v210(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x350, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 UnitDefCollectEffectRefsMaybe_4198f0(s32, s32, s32, s32, s32, s32);

extern "C" struct Obj0 * D_0048381C;

struct Obj0;

struct Obj0 {
    u8 pad000[0x64];
    s32 m64;
};

extern "C" s32 UnitCollectEffectRefsMaybe_3bd070(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    struct Obj0 *t0;
    s32 t1;
    s32 r0;
    s32 r1;

    t0 = D_0048381C;
    if (t0 == 0) {
        return p5;
    }
    t1 = t0->m64;
    if (t1 == 0) {
        return p5;
    }
    r0 = ((struct C0 *)p0)->v210((int)(long)(p1), (int)(long)(p2), (int)(long)(p3));
    if (r0 == 0) {
        return p5;
    }
    r1 = UnitDefCollectEffectRefsMaybe_4198f0(t1, r0, p2, p3, p4, p5);
    return r1;
}
