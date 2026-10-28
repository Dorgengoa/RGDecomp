/* rgp:protos */
#line 1
#include "types.h"

struct P317a90 { u8 pad0[0x7C]; s32 f7C; u8 pad80[0x48]; f32 fC8; u8 padCC[0xC4]; f32 f190; u8 pad194[0xC]; u8 f1A0[0x10]; };
struct R317a90 { u8 pad0[4]; s32 f4; u8 pad8[0xC]; s32 f14; void *f18; };

class C317a90 {
public:
    VC_VPTR_MEMBER;
    
    
    R317a90 * s003(s32 a, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(R317a90 *, (void *, s32, int, int), 0x14, a, rgp_fwd2, rgp_fwd3); }
};

extern "C" void HitShapeSetWorldCapsule_317170(void *q, void *a, void *b, s32 c, f32 x);

extern "C" R317a90 *ProjectileBuildBodyShape_317a90(P317a90 *p0, C317a90 *p1, int rgp_a2, int rgp_a3)
{
    R317a90 *r;
    void *q;

    if (!(p0->fC8 < 0.0f)) {
        return 0;
    }
    if ((p0->f7C & 2) == 0) {
        return 0;
    }
    r = p1->s003(1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r == 0) {
        return 0;
    }
    if (r->f14 <= 0) {
        q = 0;
    } else {
        q = r->f18;
    }
    HitShapeSetWorldCapsule_317170(q, p0->f1A0, (u8 *)p0 + 0x180, -1, p0->f190);
    r->f4 = p0->f7C;
    return r;
}
