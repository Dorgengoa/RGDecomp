/* rgp:protos */
#line 1
#include "types.h"

struct R412E20 { u8 pad000[0x8]; s16 f08; };
struct B412E20 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    struct R412E20 * v26(void *a, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(struct R412E20 *, (void *, void *, int, int), 0x70, a, rgp_fwd2, rgp_fwd3); }
};
struct C412E20 : B412E20 {};

extern "C" struct R412E20 *TableGetByIdChecked_412e20(struct C412E20 *p, s32 k, void *a, int rgp_a3)
{
    struct R412E20 *r;

    r = p->v26(a, (int)(long)(a), (int)(long)(rgp_a3));
    if (r == 0) return 0;
    if (r->f08 != (s16)k) return 0;
    return r;
}
