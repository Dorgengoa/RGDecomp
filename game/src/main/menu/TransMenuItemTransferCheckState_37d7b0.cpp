#include "types.h"

struct T_0037d7b0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v18() { return VCM0(s32, 0x50); }
};

struct G_0037d7b0 {
    u8 pad0[0x3C];
    s32 f3C;
};

extern "C" G_0037d7b0 *D_00484740;
extern "C" void *D_0048470C;
extern "C" u8 D_004E9230[];
extern "C" T_0037d7b0 *MenuGetSelItem_2a02d0(G_0037d7b0 *);
extern "C" void StateMachineSetState_28ede0(void *, s32, s32);
extern "C" void UiSelFrameAnimStep_28d820(void *, s32);

extern "C" s32 TransMenuItemTransferCheckState_37d7b0(void *a, void *b)
{
    T_0037d7b0 *r;
    s32 v;
    if (b == 0) goto skip;
    r = MenuGetSelItem_2a02d0(D_00484740);
    if (r != 0) goto g1;
    return 0;
g1:
    v = r->v18();
    if (v > 1) {
        D_00484740->f3C = v;
        StateMachineSetState_28ede0(D_0048470C, 0x27, 0);
    } else {
        D_00484740->f3C = 1;
        StateMachineSetState_28ede0(D_0048470C, 0x3E, 0);
    }
skip:
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
