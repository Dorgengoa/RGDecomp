/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vC0(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    
    
    
    void vF4(s32 a0) { VCM(void, (void *, s32), 0xF4, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v1A0(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A0, a0, a1, a2); }
    
    void v1A8(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A8, a0, a1, a2); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v2A8() { return VCM0(s32, 0x2A8); }
    u8 pad4[0x198 - 4];
    s32 m198;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 brest : 6;
};

struct T238 { u8 pad[0x178]; s64 m178; };
struct T20 { u8 pad[0x238]; T238 *m238; };
struct G { u8 pad[0x20]; T20 *m20; };

extern "C" s32 DoubleToUInt_13bb78(double);
extern "C" G *D_00483818;

extern "C" s32 UnitBaseKillStampTime_3b1400(Obj *o, s32 a1, s32 a2, s32 flag)
{
    T238 *t;
    s32 v;
    u8 u;
    bool one;

    if (D_00483818 == 0) {
        return 0;
    }
    if (o->vC0((int)(long)(a1), (int)(long)(a2), (int)(long)(flag)) != 0) {
        return 0;
    }
    if (o->v2A8() != 0) {
        return 0;
    }
    if (o->m198 > 0) {
        return 0;
    }
    o->b0 = 1;
    o->b1 = flag;
    o->vF4(0);
    o->v1A0(1, 1, 1);
    o->v1A8(1, 1, 1);
    t = D_00483818->m20->m238;
    if (t != 0) {
        v = DoubleToUInt_13bb78(__builtin_bit_cast(double, (long long)(t->m178)));
    } else {
        v = 0;
    }
    o->m198 = v;
    return 1;
}
