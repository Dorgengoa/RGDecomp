/* rgp:protos */
#line 1
#include "types.h"

struct B3D3680 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v23(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x64, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
struct C3D3680 : B3D3680 { u8 pad004[0x12]; s8 f16; };

extern "C" void ItemWeaponSetGrowth_3d3680(struct C3D3680 *p, s8 v, int rgp_a2, int rgp_a3)
{
    s32 r;

    p->f16 = v;
    if (v < 0) {
        p->f16 = 0;
        return;
    }
    r = p->v23((int)(long)(v), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r < p->f16) {
        p->f16 = r;
    }
}
