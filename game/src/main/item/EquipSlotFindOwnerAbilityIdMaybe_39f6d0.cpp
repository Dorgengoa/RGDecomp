/* rgp:protos */
#line 1
#include "types.h"

extern "C" s16 *AbilityListFindByDefId_3f5720(s32, s16);
class V70 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5c() { return VCM0(s32, 0x5C); }
    
    
    
    
    s32 v70(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};
class V5C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5c() { return VCM0(s32, 0x5C); }
};
class A {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5c() { return VCM0(s32, 0x5C); }
    
    
    
    
    s32 v70() { return VCM0(s32, 0x70); }
    
    
    V5C * v7c(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(V5C *, (void *, int, int, int), 0x7C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};
struct H44 { u8 pad[0xC]; V70 *mC; };
struct G { u8 pad[0x44]; H44 *m44; };
extern "C" G *D_0048374C;
class A2 : public A { public: s16 *m4; };

extern "C" s32 EquipSlotFindOwnerAbilityIdMaybe_39f6d0(A2 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s16 *p;
    s16 id;
    V5C *o;
    s32 r;

    if (D_0048374C == 0) return (s16)(-1);
    p = arg0->m4;
    if (p == 0) return (s16)(-1);
    id = *p;
    if (id < 0) return (s16)(-1);
    o = arg0->v7c((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (o == 0) return (s16)(-1);
    { s32 k = o->v5c(); r = D_0048374C->m44->mC->v70(k); }
    if (r == 0) return (s16)(-1);
    p = AbilityListFindByDefId_3f5720(r, id);
    if (p != 0) return (s16)(*p);
    return (s16)(-1);
}
