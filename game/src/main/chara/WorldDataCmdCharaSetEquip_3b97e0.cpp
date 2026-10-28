#include "types.h"

struct R8 { u8 b[8]; };

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v220(s32 b, s32 c) { VCM(void, (void *, s32, s32), 0x378, b, c); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v238(s32 a0) { VCM(void, (void *, s32), 0x3C0, a0); }
    
    
    
    
    void v243(s32 a0) { VCM(void, (void *, s32), 0x3D4, a0); }
    u8 pad004[0x230];
    u8 c0 : 1;
    u8 c1 : 1;
    u8 c2 : 6;
};

struct Ent {
    u8  pad000[0x4];
    s16 m4;
};

struct Node {
    u8  pad000[0x14];
    s32 m14;
    s32 m18;
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
};

extern "C" Pool *D_004830F8;
extern "C" s32  VariantGetInt_15f780(R8 *q);
extern "C" s32  SlotGetInt_15f720(R8 *q);
extern "C" VE  *CharaMgrPoolFindById_3a8c60(s32 a, s16 b);
extern "C" Ent *InvAddItemCoreMaybe_3c6540(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);

extern "C" s32 WorldDataCmdCharaSetEquip_3b97e0(R8 *a)
{
    Pool *p = D_004830F8;
    s16 t;
    Ent *r;
    s32 x1;
    s32 x2;
    s32 x3;
    s32 x4;
    VE *o;

    if (!p->b2) return 1;
    t = p->m9C;
    if (t < 0) return 1;
    o = CharaMgrPoolFindById_3a8c60(p->m94->m14, t);
    if (o == 0) return 1;
    if (!o->c1) return 1;

    r = InvAddItemCoreMaybe_3c6540(p->m94->m18, VariantGetInt_15f780(a++), 0, 1, -1, 0, 0);
    x1 = -1;
    if (r) x1 = r->m4;
    SlotGetInt_15f720(a++);
    r = InvAddItemCoreMaybe_3c6540(p->m94->m18, VariantGetInt_15f780(a++), 0, 1, -1, 0, 0);
    x2 = -1;
    if (r) x2 = r->m4;
    SlotGetInt_15f720(a++);
    r = InvAddItemCoreMaybe_3c6540(p->m94->m18, VariantGetInt_15f780(a++), 0, 1, -1, 0, 0);
    x3 = -1;
    if (r) x3 = r->m4;
    r = InvAddItemCoreMaybe_3c6540(p->m94->m18, VariantGetInt_15f780(a), 0, 1, -1, 0, 0);
    x4 = -1;
    if (r) x4 = r->m4;

    o->v220(0, x1);
    o->v220(1, x2);
    o->v238(x3);
    o->v243(x4);
    return 1;
}
