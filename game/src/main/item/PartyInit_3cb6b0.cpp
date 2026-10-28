/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void v5(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x1C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" {
extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e130(s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern void PoolInit_36ae50(s32, s32, s32, s32, s32);
extern void PoolCtor_36b0c0(s32);
extern s32 InvViewCtor_3cecd0(s32, u8 *, s32, s32, s32, s32);
extern s32 ItemMaxClassSize_3d58f0(void);
extern s32 D_00465B50[4];
extern s32 D_00465B58[4];
extern s32 D_00465B70[4];
extern s32 D_00483890;
extern s32 D_00483894;
extern void PartyIdPairCtor_3cb820(void);
}

extern "C" s32 PartyInit_3cb6b0(u8 *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    s32 a;
    s32 b;
    s32 c;
    s32 n;
    s32 d;

    if (arg1 == 0) {
        return 0;
    }
    D_00483890 = 0;
    D_00483894 = 0;
    *(s32 *)(arg0 + 0x168) = 0;
    *(s32 *)(arg0 + 0x170) = 0;
    *(s32 *)(arg0 + 0x174) = 0;
    *(s32 *)(arg0 + 0x17C) = 0;
    ((Obj *)arg0)->v5((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    a = MemStackNew_14e130(0x2C, arg1);
    if (a != 0) {
        PoolCtor_36b0c0(a);
    }
    *(s32 *)(arg0 + 0x168) = a;
    if (a == 0) {
        return 0;
    }
    b = MemStackNew_14e130(0x14, arg1);
    if (b != 0) {
        b = InvViewCtor_3cecd0(b, arg0, -1, -1, -1, -1);
    }
    *(s32 *)(arg0 + 0x170) = b;
    if (b == 0) {
        return 0;
    }
    c = MemStackNew_14e130(0x33C0, arg1);
    *(s32 *)(arg0 + 0x174) = c;
    if (c == 0) {
        return 0;
    }
    n = D_00465B70[0];
    d = ConstructNewArray_100710(MemStackNew_14e1b0((n * 4) + 0x10, arg1), (void *)PartyIdPairCtor_3cb820, 0, 4, n);
    *(s32 *)(arg0 + 0x17C) = d;
    if (d == 0) {
        return 0;
    }
    PoolInit_36ae50(*(s32 *)(arg0 + 0x168), arg1, ItemMaxClassSize_3d58f0(), D_00465B50[0], D_00465B58[0]);
    return 1;
}
