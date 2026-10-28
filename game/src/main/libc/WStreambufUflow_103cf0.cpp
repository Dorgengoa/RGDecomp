/* rgp:protos */
#line 1
#include "types.h"

struct C103820 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    s32 v7(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x24, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    s32 pad04;
    u8 *m08;
};

extern "C" s32 WStreambufUflow_103cf0(struct C103820 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 *q;
    s32 r;

    if (p->v7((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == -1) {
        r = -1;
    } else {
        q = p->m08;
        p->m08 = q + 4;
        r = *(u16 *)q;
    }
    return r;
}
