#include "types.h"

struct T_002aca90 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v18() { return VCM0(s32, 0x50); }
};

struct G_002aca90 {
    u8 pad0[0x3C];
    s32 f3C;
};

extern "C" s8 D_0048249C;
extern "C" G_002aca90 *D_00482374;
extern "C" void *D_0048235C;
extern "C" u8 D_004DB430[];
extern "C" T_002aca90 *MenuGetSelItem_2a02d0(G_002aca90 *);
extern "C" void StateMachineSetState_28ede0(void *, s32, s32);
extern "C" void UiSelFrameAnimStep_28d820(void *, s32);

extern "C" s32 MenuItemDiscardCheckState_2aca90(void *a, void *b)
{
    T_002aca90 *r;
    s32 v;
    if (b == 0) goto skip;
    if (D_0048249C != 0) {
        StateMachineSetState_28ede0(D_0048235C, 0x34, 0);
        goto skip;
    }
    r = MenuGetSelItem_2a02d0(D_00482374);
    if (r != 0) goto g1;
    return 0;
g1:
    v = r->v18();
    if (v > 1) {
        StateMachineSetState_28ede0(D_0048235C, 0x40, 0);
    } else {
        D_00482374->f3C = 1;
        StateMachineSetState_28ede0(D_0048235C, 0x34, 0);
    }
skip:
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
