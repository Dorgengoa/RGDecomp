/* rgp:protos */
#line 1
#include "types.h"

struct B_001e0c70 {
    u8 pad[0x1B0];
};

struct C_001e0c70 : public B_001e0c70 {
    VC_VPTR_MEMBER;
    
    
    
    void v4(f32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0, int rgp_fwd4 = 0) { VCM(void, (void *, int, int, int, f32), 0x18, rgp_fwd2, rgp_fwd3, rgp_fwd4, a0); }
    
    
    void v7() { VCM0(void, 0x24); }
};

extern "C" void MapEntryShow_1e0c70(C_001e0c70 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 q;

    q = *(s32 *)((s32)p + 0x790);
    if (q == 0) return;
    if ((*(s32 *)(q + 0x40) & 1) == 0) return;
    p->v4(1.0f, (int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    p->v7();
}
