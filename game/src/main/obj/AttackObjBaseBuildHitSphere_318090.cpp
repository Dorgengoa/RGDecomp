/* rgp:protos */
#line 1
#include "types.h"

struct R_00318090 {
    s32 f0;
    void *f4;
    s32 f8, fC, f10, f14;
    void *f18;
};

struct C_00318090 {
    VC_VPTR_MEMBER;
    
    
    R_00318090 * v3(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(R_00318090 *, (void *, s32, int, int), 0x14, a0, rgp_fwd2, rgp_fwd3); }
};

struct T_00318090 {
    u8 pad[0x7C];
    s32 f7C;
    u8 pad2[0x180 - 0x80];
    f32 f180;
    u8 pad3[0xC];
    f32 f190;
};

extern "C" void HitShapeSetSphere_3171d0(void *, f32 *, s32, f32);

extern "C" R_00318090 *AttackObjBaseBuildHitSphere_318090(T_00318090 *p, C_00318090 *c, int rgp_a2, int rgp_a3)
{
    R_00318090 *r;
    void *a;

    r = c->v3(1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r == 0) return 0;
    if (r->f14 <= 0) {
        a = 0;
    } else {
        a = r->f18;
    }
    HitShapeSetSphere_3171d0(a, &p->f180, -1, p->f190);
    r->f4 = (void *)p->f7C;
    return r;
}
