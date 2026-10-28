/* rgp:protos */
#define RGP_SELF_TopMenuOpen_2969b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00461198[];
extern u8 D_004611A8[];
extern f32 D_0047D5D0;
extern f32 D_0047D6CC;
extern f32 D_0047D7AC;
extern s32 D_00482350;
extern s16 D_0048239C;
extern u8 D_004DB1B0[];

s32 TopMenuOpen_2969b0(s32 arg0, s32 arg1) {
    s32 x;
    s32 i;
    s32 y;
    u16 id;
    f32 fx;

    if (arg1 != 0) {
        UiSetWidgetsVisibleById_291110(D_004DB1B0, 0xB, 1, 1);
        UiSetWidgetPos_290f60(D_004DB1B0, 0xC, 5, 5);
        UiSetWidgetColor_2905b0(D_004DB1B0, 0xC, 0.0f, 0.0f, 0.0f, D_0047D6CC);
        UiSetWidgetPos_290f60(D_004DB1B0, 0xB, -0x30, -0xF);
        UiMoveWidgetUniform_290f50(D_004DB1B0, 0xB, 0, 0, D_0047D5D0, 0);
        UiFadeWidgetAlpha_290690(D_004DB1B0, 0xB, 1.0f, D_0047D7AC, 0.0f);
        x = -0x40;
        if (D_0048239C != 0) {
            x = 0x21;
        }
        for (i = 0; i < 8; i++) {
            y = i * 39;
            UiSetWidgetPos_290f60(D_004DB1B0, i + 0x16, x, y + 0x50);
            id = i + 0xD;
            UiSetWidgetPos_290f60(D_004DB1B0, id, x + 3, y + 0x53);
            UiSetWidgetColor_2905b0(D_004DB1B0, id, 0.0f, 0.0f, 0.0f, D_0047D6CC);
            UiSetWidgetsVisibleById_291110(D_004DB1B0, i + 0x1E, 1, 1);
            fx = (i / 2) * 64 + 0x20;
            id = i + 0x39;
            UiSetSpriteU_28f930(D_004DB1B0, id, fx, 0);
            if (i == 4) {
                if (TopMenuIsHunterUnlocked_29ac90() == 0) {
                    MainMenuPanelSetWidgetTex_297850(id, D_00461198, 0x60, 0x60, 0x20);
                } else {
                    MainMenuPanelSetWidgetTex_297850(id, D_004611A8, fx, 0xC1, 0x1F);
                }
            } else if (i == 5) {
                if (TopMenuRow5UnlockedMaybe_29ac50() == 0) {
                    MainMenuPanelSetWidgetTex_297850(id, D_00461198, 0x60, 0x60, 0x20);
                } else {
                    MainMenuPanelSetWidgetTex_297850(id, D_004611A8, fx, 0xE1, 0x1F);
                }
            } else if (i == 6) {
                if (TopMenuRow6UnlockedMaybe_29ac20() == 0) {
                    MainMenuPanelSetWidgetTex_297850(id, D_00461198, 0x60, 0x60, 0x20);
                } else {
                    MainMenuPanelSetWidgetTex_297850(id, D_004611A8, fx, 0xC1, 0x1F);
                }
            }
        }
    }
    if (UiWidgetIsMoving_290d30(D_004DB1B0, 0xB) == 0) {
        StateMachineSetState_28ede0(&D_00482350, 2, 0);
    }
    return 1;
}
