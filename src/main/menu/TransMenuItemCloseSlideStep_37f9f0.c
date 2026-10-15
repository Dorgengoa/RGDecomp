#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s16 unk8;
} Sub0037f9f0;

typedef struct {
    u8 pad0[0x20];
    Sub0037f9f0 *unk20;
} Item0037f9f0;

extern void UiPlaceRowWidgetPairMaybe_28cf40(s32, s32, s32, s32, s32);
extern Item0037f9f0 *UiFindWidget_290460(s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern f32 D_0047D5D0;
extern f32 D_0047D990;
extern f32 D_0047D994;
extern s32 D_0048324C;
extern s32 D_00484710;

s32 TransMenuItemCloseSlideStep_37f9f0(void)
{
    s32 sp1C;
    s32 sp18;
    Item0037f9f0 *it;
    Sub0037f9f0 *sub;

    switch (D_0048324C) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 0, 0x753E, 0x7539, D_00484710);
        UiMoveWidgetUniform_290f50(D_00484710, 0x7547, 0x104, -0x19, 0, D_0047D5D0);
        UiMoveWidgetUniform_290f50(D_00484710, 0x7546, 0x10A, -0x13, 0, D_0047D5D0);
        UiGetWidgetPos_2910a0(D_00484710, 0x753E, &sp1C, &sp18);
        if (sp1C < 0x1F) {
            D_0048324C = 1;
            UiFadeWidgetAlpha_290690(D_00484710, 0x7553, 0.0f, D_0047D990, -1.0f);
        }
        break;
    case 1:
        UiFadeWidgetAlpha_290690(D_00484710, 0x7552, 1.0f, D_0047D994, -1.0f);
        it = UiFindWidget_290460(D_00484710, 0x7552);
        it->unk20->unk8 = 0xE0;
        D_0048324C = 4;
        break;
    }
    return 0;
}
