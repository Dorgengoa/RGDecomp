/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineShowMsg_362490 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct {
    u8 pad0[0x84];
    s32 unk84;
} O00362490;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MenuWeaponCombineShowMsg_362490(O00362490 *arg0, s32 arg1, s32 arg2)
{
    s32 a;
    s32 b;

    UiSetTextString_28f510(arg0->unk84, 0x1E8, arg1, 0);
    if (arg2 != 0) {
        UiSetWidgetAlpha_2907a0(arg0->unk84, 0x1E7, 1.0f);
        UiFadeWidgetAlpha_290690(arg0->unk84, 0x1E7, 1.0f, 1.0f, 1.0f);
    } else {
        UiFadeWidgetAlpha_290690(arg0->unk84, 0x1E7, 1.0f, 0.0625f, -1.0f);
    }
    UiGetWidgetTextSize_28f430(arg0->unk84, 0x1E8, &a, &b, 0);
    if (a < 0x28) {
        a = 0x28;
    }
    a -= 0xC;
    UiSetSpriteW_28fbf0(arg0->unk84, 0x1E8, a, 1);
    UiSetSpriteW_28fbf0(arg0->unk84, 0x1E8, a, 4);
    UiSetSpriteW_28fbf0(arg0->unk84, 0x1E8, a, 7);
    UiSetSpriteX_28fcd0(arg0->unk84, 0x1E8, a + 0x29, 2);
    UiSetSpriteX_28fcd0(arg0->unk84, 0x1E8, a + 0x29, 5);
    UiSetSpriteX_28fcd0(arg0->unk84, 0x1E8, a + 0x29, 8);
    if (b > 8) {
        b -= 0xC;
        UiSetSpriteH_28fbb0(arg0->unk84, 0x1E8, b, 3);
        UiSetSpriteH_28fbb0(arg0->unk84, 0x1E8, b, 4);
        UiSetSpriteH_28fbb0(arg0->unk84, 0x1E8, b, 5);
        UiSetTextY_28f550(arg0->unk84, 0x1E8, 0x108 - b, 0);
        UiSetSpriteY_28fc90(arg0->unk84, 0x1E8, 0xFE - b, 0);
        UiSetSpriteY_28fc90(arg0->unk84, 0x1E8, 0xFE - b, 1);
        UiSetSpriteY_28fc90(arg0->unk84, 0x1E8, 0xFE - b, 2);
        UiSetSpriteY_28fc90(arg0->unk84, 0x1E8, 0x10E - b, 3);
        UiSetSpriteY_28fc90(arg0->unk84, 0x1E8, 0x10E - b, 4);
        UiSetSpriteY_28fc90(arg0->unk84, 0x1E8, 0x10E - b, 5);
    }
}
