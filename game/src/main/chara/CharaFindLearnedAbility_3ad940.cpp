/* rgp:protos */
#line 1
#include "types.h"

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s16 x0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, x0, rgp_fwd2, rgp_fwd3); }
};

extern "C" {
extern s32 Fprintf_12f9a0(s32, void *);
extern void Abort_12de80(void);
extern s16 *AbilityListFindByCompositeId_3f5670(s32, s32, s32);
extern u8 *D_00449858[0x100];
extern u8 D_00465ED0[];
extern u8 *D_0048381C;
}

class Bit3AD940 {
public:
    s64 *p;
    u32 n;
    Bit3AD940(s64 *pp, u32 nn) : p(pp), n(nn) {}
    s64 Get()
    {
        u32 k = n;
        if (k >= 0x40) {
            Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00465ED0);
            Abort_12de80();
        }
        return *p & (1LL << k);
    }
};

extern "C" s32 CharaFindLearnedAbility_3ad940(u8 *arg0, s32 arg1, s32 arg2, int rgp_a3)
{
    s32 result;
    s16 *p3;
    s32 i;
    s32 t2;
    s16 *node;

    if (D_0048381C == 0 || (p3 = *(s16 **)(arg0 + 0x230)) == 0) {
        return 0;
    }
    if ((t2 = (*(VC_0 **)(*(u8 **)(D_0048381C + 0x44) + 0xC))->f(*p3, (int)(long)(arg2), (int)(long)(rgp_a3))) == 0) {
        return 0;
    }
    result = 0;
    i = 0;
    for (;;) {
        node = AbilityListFindByCompositeId_3f5670(t2, arg1, i);
        if (node == 0) {
            if (i == 0) {
            } else {
                break;
            }
        } else {
            if (Bit3AD940((s64 *)(arg0 + (arg2 & 0xFF) * 8 + 0x2E0), *node - 1).Get()) {
                result = *(s32 *)(node + 2);
                break;
            }
        }
        i++;
    }
    return result;
}
