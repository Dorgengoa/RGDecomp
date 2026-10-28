/* rgp:protos */
#line 1
#include "types.h"

class VE {
public:
    u8 pad000[0x14];
    VC_VPTR_MEMBER; void v0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x8, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void *D_00470598[];

extern "C" void *FuncDataTableNodeCtor_190d50(VE *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    *(void **)((u8 *)o + 0x14) = (void *)D_00470598;
    o->v0((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return o;
}
