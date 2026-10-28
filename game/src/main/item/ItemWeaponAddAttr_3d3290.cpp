/* rgp:protos */
#line 1
#include "types.h"

struct B3D3290 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v38(s32 i, s32 v, int rgp_fwd3 = 0) { VCM(void, (void *, s32, s32, int), 0xA0, i, v, rgp_fwd3); }
};
struct C3D3290 : B3D3290 {};

extern "C" s32 ItemWeaponAddAttr_3d3290(struct C3D3290 *p, s32 i, s32 a, int rgp_a3)
{
    s8 *base;
    s8 *q;

    if (i < 0 || i >= 5) return 0;
    base = (s8 *)(i + (s32)p);
    q = base + 0x17;
    p->v38(i, *q + a, (int)(long)(rgp_a3));
    return *q;
}
