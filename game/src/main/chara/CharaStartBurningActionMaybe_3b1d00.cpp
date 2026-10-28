/* rgp:protos */
#line 1
#include "types.h"

class B {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v280(void * a0) { VCM(void, (void *, void *), 0x280, a0); }
};
class O {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    bool v228(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return (vc_u8)VCM(vc_u32, (void *, int, int, int), 0x228, rgp_fwd1, rgp_fwd2, rgp_fwd3) != 0; }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v288(void * a0, s32 a1, s32 a2, s32 a3, s32 a4) { VCM(void, (void *, void *, s32, s32, s32, s32), 0x288, a0, a1, a2, a3, a4); }
    
    
    
    
    s32 v29C(s32 a0, s32 a1) { return VCM(s32, (void *, s32, s32), 0x29C, a0, a1); }
    u8 pad004[0x8];
    s32 xC;
    u8 pad010[0x1CC];
    s32 x1DC;
};

typedef struct B70 { u8 pad[0x48]; s64 b8; s64 c0; s64 c8; s64 d0; u8 pad2[0x28]; } B70;
typedef struct G { u8 pad[0x14]; s32 x14; } G;
extern "C" void ActionResultSetupMaybe_3a6d70(void *, void *, s32, s32, s32, s32, f32);
extern "C" void ActionResultClear_3a6e60(void *);
extern "C" void ExecInfoInitFromChara_3a7830(void *, s32, s32, s32, void *);
extern "C" void ExecInfoInit_3a7940(void *);
extern "C" B *CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" u8 D_00465EF8[];
extern "C" G *D_00483818;

extern "C" s32 CharaStartBurningActionMaybe_3b1d00(O *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    u8 sp100[0x70] __attribute__((aligned(16)));
    B70 sp70 __attribute__((aligned(16)));
    s32 f;
    s32 id;
    s32 r;
    B *b;

    f = arg0->v228((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    id = arg0->x1DC;
    r = arg0->v29C(id, 0);
    arg0->x1DC = 0;
    ExecInfoInit_3a7940(sp100);
    b = CharaMgrPoolFindById_3a8c60(D_00483818->x14, arg1);
    if (b != 0) {
        ExecInfoInitFromChara_3a7830(sp100, arg1, 0, 0, D_00465EF8);
        b->v280(sp100);
    }
    sp70.b8 = 0;
    sp70.c0 = 0;
    sp70.c8 = 0;
    sp70.d0 = 0;
    ActionResultClear_3a6e60(&sp70);
    ActionResultSetupMaybe_3a6d70(&sp70, sp100, arg0->xC, 0, 0, 1, 0.0f);
    arg0->v288(&sp70, id, 0, 0, f);
    return r;
}
