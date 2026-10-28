/* rgp:protos */
#line 1
#include "types.h"

struct B3AD0F0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v12(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x38, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
struct C3AD0F0 : B3AD0F0 {};

extern "C" s32 CharaUnequipWeapon_3ad0f0(struct C3AD0F0 *p, s32 k, int rgp_a2, int rgp_a3)
{
    s32 off;

    if (k == 0) goto ok;
    if (k == 1) goto ok;
    return 0;
ok:
    off = k * 2;
    *(s16 *)(off + (s32)p + 0x23E) = -1;
    p->v12((int)(long)(k), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return 1;
}
