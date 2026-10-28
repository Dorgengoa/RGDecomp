/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_loop_invariants off
class V {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void s5() { VCM0(void, 0x1C); }
};

extern "C" {
extern void UnitCtorReset_3b8a80(void *);
extern void Fill3U64Default_3b0990(void *);
extern u8 D_004731D0[0x400];
extern u8 D_00471FE0[0x400];
extern u8 D_004720E0[0x400];
extern u8 D_00472170[0x400];
extern u8 D_00473BF0[0x400];
extern u8 D_00474100[0x400];
extern u8 D_00474440[0x400];
}

extern "C" void *CharaKind1002Ctor_3a9090(u8 *arg0)
{
    u8 *var_5;
    u8 *var_16;
    u8 *temp_4;

    *(u8 **)(arg0 + 0) = D_00471FE0;
    *(u8 **)(arg0 + 0) = D_00474440;
    UnitCtorReset_3b8a80(arg0);
    *(u8 **)(arg0 + 0) = D_00474100;
    var_5 = arg0 + 0x2E0;
    temp_4 = arg0 + 0x2F0;
    *(s64 *)(arg0 + 0xC8) = 0;
    *(s64 *)(arg0 + 0x1A8) = 0;
    *(s64 *)(arg0 + 0x1B8) = 0;
    *(u8 **)(arg0 + 0) = D_00473BF0;
    *(s32 *)(arg0 + 0x238) = 0x54;
    do {
        *(s64 *)var_5 = 0;
        var_5 += 8;
    } while ((u32)var_5 < (u32)temp_4);
    Fill3U64Default_3b0990((void *)(((__typeof__(arg0))((unsigned)(arg0) + 0x2f0))));
    var_16 = arg0 + 0x308;
    do {
        *(u8 **)var_16 = D_00471FE0;
        *(u8 **)var_16 = D_00472170;
        ((V *)var_16)->s5();
        *(u8 **)var_16 = D_004720E0;
        ((V *)var_16)->s5();
        var_16 += 0x28;
    } while ((u32)var_16 < (u32)(arg0 + 0x498));
    *(u8 **)arg0 = D_004731D0;
    return arg0;
}
