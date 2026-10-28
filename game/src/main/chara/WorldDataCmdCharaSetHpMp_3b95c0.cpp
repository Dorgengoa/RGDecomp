#include "types.h"

struct R8 { u8 b[8]; };

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void v12() { VCM0(void, 0x38); }
    void v13() { VCM0(void, 0x3C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v59(s16 a) { VCM(void, (void *, s16), 0xF4, a); }
    
    
    
    
    
    
    void v66(s16 a) { VCM(void, (void *, s16), 0x110, a); }
    
    
    
    
    
    s32 v72(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }
    
    s32 v74(s32 a) { return VCM(s32, (void *, s32), 0x130, a); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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
extern "C" VE *CharaMgrPoolFindById_3a8c60(s32 a, s16 b);

extern "C" s32 WorldDataCmdCharaSetHpMp_3b95c0(R8 *a)
{
    Pool *p = D_004830F8;
    s16 t;
    VE *o;

    if (!p->b2) return 1;
    t = p->m9C;
    if (t < 0) return 1;
    o = CharaMgrPoolFindById_3a8c60(p->m94->m14, t);
    if (o == 0) return 1;
    if (p->m9E <= 0) p->m9E = o->v72(1);
    if (p->mA0 < 0) p->mA0 = o->v74(1);
    o->v274();
    o->v12();
    o->v59(p->m9E);
    o->v66(p->mA0);
    o->v13();
    return 1;
}
