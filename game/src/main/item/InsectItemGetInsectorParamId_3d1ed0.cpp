/* rgp:protos */
#line 1
#include "types.h"

struct S3D1ED0 { s16 f0; };

class C3D1ED0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    struct S3D1ED0 * vcall(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(struct S3D1ED0 *, (void *, int, int, int), 0x124, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" s32 InsectItemGetInsectorParamId_3d1ed0(C3D1ED0 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct S3D1ED0 *r;

    r = p->vcall((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r != 0) {
        return r->f0;
    }
    return -1;
}
