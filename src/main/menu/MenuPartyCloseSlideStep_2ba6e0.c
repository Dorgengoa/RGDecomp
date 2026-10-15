#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s16 unk8;
} Node002ba6e0;

typedef struct {
    u8 pad0[0x20];
    Node002ba6e0 *unk20;
} Obj002ba6e0;

extern void UiPlaceRowWidgetPairMaybe_28cf40(s32, s32, s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern Obj002ba6e0 *UiFindWidget_290460(s32, s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern f32 D_0047D6C0;
extern f32 D_0047D6C8;
extern s32 D_00482360;
extern s32 D_00482564;

s32 MenuPartyCloseSlideStep_2ba6e0(void) {
    s32 sp1C;
    s32 sp18;

    switch (D_00482564) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 1, 0x17, 0xE, D_00482360);
        UiGetWidgetPos_2910a0(D_00482360, 0x17, &sp1C, &sp18);
        if (sp1C < 0x1F) {
            D_00482564 = 1;
            UiFadeWidgetAlpha_290690(D_00482360, 0x41, 0.0f, D_0047D6C0, -1.0f);
        }
        break;
    case 1: {
        Obj002ba6e0 *obj;

        UiGetWidgetAlpha_290770(D_00482360, 0x41);
        UiFadeWidgetAlpha_290690(D_00482360, 0x3A, 1.0f, D_0047D6C8, -1.0f);
        obj = UiFindWidget_290460(D_00482360, 0x3A);
        obj->unk20->unk8 = 0x20;
        D_00482564 = 3;
        break;
    }
    }
    return 0;
}
