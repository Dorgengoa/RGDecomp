#include "types.h"

struct R8 { u8 b[8]; };

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v57(s32 a0) { VCM(void, (void *, s32), 0xEC, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v263(s32 a0) { VCM(void, (void *, s32), 0x424, a0); }
    
    
    
    
    
    
    
    
    
    
    void v274() { VCM0(void, 0x450); }
};

struct Node {
    u8  pad000[0x14];
    s32 m14;
};

struct Pool {
    u8    pad000[0x94];
    Node *m94;
    u8    pad098[0x2];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
    u8    pad09B[0x1];
    s16   m9C;
    s16   m9E;
    s16   mA0;
};

extern "C" Pool *D_004830F8;
extern "C" s32 VariantGetInt_15f780(R8 *q);
extern "C" VE *CharaMgrPoolFindById_3a8c60(s32 a, s16 b);

extern "C" s32 WorldDataCmdCharaSetLevelExp_3b99f0(R8 *a)
{
    Pool *p = D_004830F8;
    s16 t;
    s32 v1;
    s32 v2;
    VE *o;
    s32 v3;
    s32 v4;

    if (!p->b2) return 1;
    t = p->m9C;
    if (t < 0) return 1;
    o = CharaMgrPoolFindById_3a8c60(p->m94->m14, t);
    if (o == 0) return 1;
    v1 = VariantGetInt_15f780(a++);
    v2 = VariantGetInt_15f780(a++);
    v3 = VariantGetInt_15f780(a++);
    v4 = VariantGetInt_15f780(a++);
    o->v263(v2);
    o->v57(v1);
    o->v274();
    p->m9E = v3;
    p->mA0 = v4;
    return 1;
}
