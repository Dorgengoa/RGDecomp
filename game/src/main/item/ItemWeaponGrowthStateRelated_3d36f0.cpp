/* rgp:protos */
#line 1
#include "types.h"

struct B3D36F0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v23(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x64, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
struct C3D36F0 : B3D36F0 { u8 pad004[0x12]; s8 f16; };

extern "C" s32 ItemWeaponGrowthStateRelated_3d36f0(struct C3D36F0 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 v;
    s32 r;

    v = p->f16;
    r = p->v23((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (v < r) {
        return 2;
    }
    return 0;
}
