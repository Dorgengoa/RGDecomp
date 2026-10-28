/* rgp:protos */
#define RGP_SELF_MenuItemCloseSlideStep_2b1cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x8];
    s16 unk8;
} Sub0037f9f0;

typedef struct {
    u8 pad0[0x20];
    Sub0037f9f0 *unk20;
} Item0037f9f0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D5D0;
extern f32 D_0047D76C;
extern f32 D_0047D77C;
extern s32 D_004824D8;
extern s32 D_00482360;

s32 MenuItemCloseSlideStep_2b1cf0(void)
{
    s32 sp1C;
    s32 sp18;
    Item0037f9f0 *it;
    Sub0037f9f0 *sub;

    switch (D_004824D8) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 0, 0x16, 0xD, D_00482360);
        UiMoveWidgetUniform_290f50(D_00482360, 0x2E, 0x104, -0x19, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x2D, 0x10A, -0x13, D_0047D5D0, 0);
        UiGetWidgetPos_2910a0(D_00482360, 0x16, &sp1C, &sp18);
        if (sp1C < 0x1F) {
            D_004824D8 = 1;
            UiFadeWidgetAlpha_290690(D_00482360, 0x41, 0.0f, D_0047D76C, -1.0f);
        }
        break;
    case 1:
        UiGetWidgetAlpha_290770(D_00482360,0x41);
        UiFadeWidgetAlpha_290690(D_00482360, 0x39, 1.0f, D_0047D77C, -1.0f);
        it = ((Item0037f9f0 *)UiFindWidget_290460(D_00482360, 0x39));
        it->unk20->unk8 = 0x20;
        D_004824D8 = 3;
        break;
    }
    return 0;
}
