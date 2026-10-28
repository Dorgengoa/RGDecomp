#include "types.h"
#undef NULL
#define NULL 0

typedef struct Obj18 {
    u8 pad18[0x18];
    s32 unk18;
} Obj18;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x3E0); }
};

extern "C" {
Obj18 *GetGameData_1fede0(void);
void UiSelFrameAnimStep_28d820(void *, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void UiFadeWidgetColor_2904e0(s32, s32, f32, f32, f32, f32, f32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
f32 UiGetWidgetAlpha_290770(s32, s32);
void MenuPartyCharaIconsLayoutMaybe_29ad30(s32, s32, s16);
void MenuSetPartyEquipIcon_29ec60(s32, s32, s32, s32);
void MenuSetGridSel_29f9b0(s32, s32, s32, s32);
s32 MenuGetCursorIndex_29fa80(s32);
void MenuWidgetFadeInOut_29fb00(s32, s32, s32, s32);
VC_0 *PartyGetSlotChara_3c2fb0(s32, s32);
extern f32 D_0047D35C;
extern f32 D_0047D5D0;
extern f32 D_0047D674;
extern f32 D_0047D6A0;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482370;
extern s16 D_00482574;
extern u8 D_004DB790[];
}

extern "C" s32 MenuEquipRemoveFlashState_2b66e0(s32 arg0, s32 arg1)
{
    f32 f;
    s16 n;
    Obj18 *o;
    s32 id;
    VC_0 *v;

    if (arg1 != 0) {
        D_00482574 = 0;
        UiFadeWidgetAlpha_290690(D_00482360, 0x185, 0.0f, D_0047D6A0, -1.0f);
    } else {
        f = UiGetWidgetAlpha_290770(D_00482360, 0x185);
        if (f < D_0047D5D0) {
            if (D_00482574 == 0) {
                UiFadeWidgetColor_2904e0(D_00482360, 0x131, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D5D0);
                D_00482574 = 1;
            }
        }
        if (D_00482574 != 0) {
            f = UiGetWidgetAlpha_290770(D_00482360, 0x131);
            if (!(f < D_0047D35C)) {
                UiFadeWidgetColor_2904e0(D_00482360, 0x131, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D674);
            } else {
                if (f <= 1.0f) {
                    n = D_00482574 + 1;
                    D_00482574 = n;
                    if (n > 7) {
                        o = GetGameData_1fede0();
                        id = MenuGetCursorIndex_29fa80(D_00482370);
                        v = PartyGetSlotChara_3c2fb0(o->unk18, id);
                        if (v == NULL) {
                            return 0;
                        }
                        v->f();
                        MenuSetPartyEquipIcon_29ec60(D_00482370, id, 0x116, 3);
                        MenuSetGridSel_29f9b0(D_00482370, 0, 0, 0);
                        MenuPartyCharaIconsLayoutMaybe_29ad30(D_00482370, 0xDB, id);
                        StateMachineSetState_28ede0(D_0048235C, 0x5C, 0);
                    } else if (n == 3) {
                        MenuWidgetFadeInOut_29fb00(D_00482370, 0x12F, 0, 0);
                    }
                }
            }
        }
    }
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
