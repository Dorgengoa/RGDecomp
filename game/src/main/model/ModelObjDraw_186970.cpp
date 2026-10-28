/* rgp:protos */
#line 1
#include "types.h"

struct Base {
    u8 pad000[0x1B0];
};

class A : public Base {
public:
    VC_VPTR_MEMBER;
    
    
    s32 v3(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x14, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void *GetDrawCtx_15de80(void);
extern "C" s32 ModelDraw_14f6d0(class A *a, void *b, void *c);

extern "C" s32 ModelObjDraw_186970(class A *a, int rgp_a1, int rgp_a2, int rgp_a3)
{
    if (a->v3((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
        return 0;
    }
    return ModelDraw_14f6d0(a, GetDrawCtx_15de80(), (u8 *)a + 0x120);
}
