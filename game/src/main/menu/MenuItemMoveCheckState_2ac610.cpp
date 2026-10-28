#include "types.h"

struct T_002ac610 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v18() { return VCM0(s32, 0x50); }
};

struct G_002ac610 {
    u8 pad0[0x3C];
    s32 f3C;
};

extern "C" G_002ac610 *D_00482374;
extern "C" void *D_0048235C;
extern "C" void *D_00482360;
extern "C" f32 D_0047D70C;
extern "C" u8 D_004DB430[];
extern "C" T_002ac610 *MenuGetSelItem_2a02d0(G_002ac610 *);
extern "C" void StateMachineSetState_28ede0(void *, s32, s32);
extern "C" void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern "C" void UiSelFrameAnimStep_28d820(void *, s32);

extern "C" s32 MenuItemMoveCheckState_2ac610(void *a, void *b)
{
    T_002ac610 *r;
    s32 v;
    if (b == 0) goto skip;
    r = MenuGetSelItem_2a02d0(D_00482374);
    if (r != 0) goto g1;
    return 0;
g1:
    v = r->v18();
    if (v > 1) {
        StateMachineSetState_28ede0(D_0048235C, 0x40, 0);
    } else {
        D_00482374->f3C = 1;
        StateMachineSetState_28ede0(D_0048235C, 0xD, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D70C, -1.0f);
    }
skip:
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
