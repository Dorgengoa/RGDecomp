#include "types.h"

extern "C" struct rgp_anon_D_00465D78 { s32 v; s32 pad[3]; } D_00465D78;
extern "C" s32 D_004838EC;
extern "C" s16 D_004801DE[4];

struct Sub { u8 pad[0x27]; s8 lv; };
class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v104(s32 a0) { return VCM(s32, (void *, s32), 0x1A8, a0); }
    u8 pad4[0x14];
    Sub *p18;
};

extern "C" s32 InsectItemGetNextLevelExp_3d1820(VE *o)
{
    return o->v104(o->p18->lv + 1);
}

extern "C" s32 func_003D1840(VE *o, s32 n)
{
    if (n <= 1 || D_00465D78.v + 1 < n) return 0;
    if (D_004838EC) return D_004801DE[n];
    return 0;
}
