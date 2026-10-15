#include "types.h"
#pragma opt_propagation off
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT5C {
    u8 pad[0x5C];
    s32 (*unk5C)(void *);
} VT5C;

typedef struct Obj0 {
    VT5C *unk0;
    u8 padC[8];
    s32 unkC;
} Obj0;

typedef struct Obj18 {
    u8 pad18[0x18];
    s32 unk18;
} Obj18;

Obj18 *GetGameData_1fede0(...);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
void RevelationBoardSetCharaPortrait_349660(void *);
void MenuGridGetCursor_34d060(s32, s32 *, s32 *);
void RevelationBoardCursorUpdateMaybe_34d080(s32, s32, s32, s32);
Obj0 *PartyGetSlotChara_3c2fb0(s32, s8);
void RevelationBoardRefreshMaybe_3eaec0(void *, s32, s32);
extern s32 D_0047F6C0;
extern s32 D_0047F6C4;
extern s32 D_0048235C;
extern s32 D_00482360;
extern u8 *D_00482378;
extern s32 D_0048238C;

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual s32 f();
};
s32 RevelationBoardFocusChara_345ed0(s32 pad0, s32 arg1) {
    s32 arg_h0;

    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 temp_2_3;
    s32 var_2;
    s32 var_2_2;
    s32 var_2_3;
    Obj18 *temp_2;
    Obj0 *temp_2_2;

    temp_2 = GetGameData_1fede0();
    if (temp_2 == NULL) {
        return 1;
    }
    temp_2_2 = PartyGetSlotChara_3c2fb0(temp_2->unk18, *(s8 *)(D_00482378 + 0x6C));
    if (temp_2_2 == NULL) {
        return 1;
    }
    RevelationBoardSetCharaPortrait_349660(temp_2_2);
    temp_2_3 = ((VC_0 *)(temp_2_2))->f();
    D_0047F6C4 = temp_2_3;
    D_0047F6C0 = temp_2_2->unkC;
    if (arg1 != 0) {
        RevelationBoardRefreshMaybe_3eaec0(temp_2, temp_2_3, 0);
    }
    RevelationBoardCursorUpdateMaybe_34d080(D_0048238C, D_0047F6C0, D_0047F6C4, 1);
    UiGetWidgetPos_2910a0(D_00482360, 0x47, &sp4C, &sp48);
    sp44 = 0;
    sp40 = 0;
    MenuGridGetCursor_34d060(D_0048238C, &sp44, &sp40);
    if (sp44 <= 0x9f) {
        var_2 = sp4C + (0xA0 - sp44);
        sp4C = var_2;
    } else {
        if (sp44 > 0x160) {
            var_2 = sp4C - (sp44 - 0x160);
            sp4C = var_2;
        }
    }
    if (sp40 <= 0x9f) {
        var_2_2 = sp48 + (0xA0 - sp40);
        sp48 = var_2_2;
    } else {
        if (sp40 > 0x120) {
            var_2_2 = sp48 - (sp40 - 0x120);
            sp48 = var_2_2;
        }
    }
    if (sp4C <= -547) {
        sp4C = -0x222;
    } else if (sp4C >= 1) {
        sp4C = 0;
    }
    if (sp48 <= -449) {
        var_2_3 = -0x1C0;
        sp48 = var_2_3;
    } else {
        if (sp48 > 0x50) {
            var_2_3 = 0x50;
            sp48 = var_2_3;
        }
    }
    UiSetWidgetPos_290f60(D_00482360, 0x47, sp4C, sp48);
    StateMachineSetState_28ede0(D_0048235C, 0xB6, 0);
    return 1;
}

}
