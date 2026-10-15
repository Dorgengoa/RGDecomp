#include "types.h"

struct T_0037d530 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual s32 v18();
};

struct G_0037d530 {
    u8 pad0[0x3C];
    s32 f3C;
};

extern "C" G_0037d530 *D_00484740;
extern "C" void *D_0048470C;
extern "C" u8 D_004E9230[];
extern "C" T_0037d530 *MenuGetSelItem_2a02d0(G_0037d530 *);
extern "C" void StateMachineSetState_28ede0(void *, s32, s32);
extern "C" void UiSelFrameAnimStep_28d820(void *, s32);

extern "C" s32 TransMenuItemDiscardCheckState_37d530(void *a, void *b)
{
    T_0037d530 *r;
    s32 v;
    if (b == 0) goto skip;
    r = MenuGetSelItem_2a02d0(D_00484740);
    if (r != 0) goto g1;
    return 0;
g1:
    v = r->v18();
    if (v > 1) {
        D_00484740->f3C = 1;
        StateMachineSetState_28ede0(D_0048470C, 0x27, 0);
    } else {
        D_00484740->f3C = 1;
        StateMachineSetState_28ede0(D_0048470C, 0x2B, 0);
    }
skip:
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
