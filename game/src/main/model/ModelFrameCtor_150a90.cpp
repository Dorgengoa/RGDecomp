/* rgp:protos */
#line 1
#include "types.h"

class VE {
public:
    u8 pad000[0xE0];
    VC_VPTR_MEMBER;
    
    void v2(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void *D_0046FFA0[];

extern "C" void *ModelFrameCtor_150a90(VE *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    *(void **)((u8 *)o + 0xE0) = (void *)D_0046FFA0;
    o->v2((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return o;
}
